//
// Created by miles on 5/25/2022.
//

#include "../../../Graphic/DerivedClasses/Texture/Texture.h"
#include "../../../Singleton/DerivedClasses/Scene/DerivedClasses/Overworld/Overworld.h"
#include "../../../Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.h"
#include "../../../Singleton/DerivedClasses/Mixer/Mixer.h"
#include "../../../Singleton/DerivedClasses/KeyManager/KeyManager.h"
#include "../Character/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "Item.h"

Item::Item(int n) : quantity(n) {}

Item::Item(int n, int x, int y) : Entity(x, y), quantity(n) {}

int Item::getQuantity() const {
    return this->quantity;
}

void Item::add(const int n) {
    this->quantity += n;
}

void Item::use() {
    if (this->quantity > 0) {
        --this->quantity;
    }
}

std::string Item::useMessage() const {
    std::string message("You used a");

    if (isVowel(this->getName()[0])) {
        message += 'n';
    }

    return message.append(' ' + this->getName() + '!');
}

std::string Item::noEffectMessage(const Pokemon &pokemon) const {
    return this->getName() + " had no effect on " + pokemon.getName() + ".\n";
}

void Item::interact() {
    if (not GraphicsEngine::getInstance().hasAny<TextBox>()) {
        KeyManager::getInstance().lockKey(SDL_Scancode::SDL_SCANCODE_RETURN);

        Player::getPlayer().setState(Character::State::IMMOBILE);
        Overworld::createTextBox(
                "You obtained a" + std::string(isVowel(this->getName()[0]) ? "n " : " ") + this->getName() + '!'
        );
        Mix_PauseMusic();
        Mixer::getInstance().playSound("item_found");
        Mix_ChannelFinished([](int c) -> void {
            KeyManager::getInstance().unlockKey(SDL_Scancode::SDL_SCANCODE_RETURN);
            Mix_ResumeMusic();
        });
    }
    else if (not GraphicsEngine::getInstance().getGraphic<TextBox>().isPrinting()) {
        GraphicsEngine::getInstance().removeGraphic<TextBox>();
        Player::getPlayer().setState(Character::State::IDLE);

        // add the item to the Player's inventory and remove it from the map
        Player::getPlayer().addItem(this->getName(), this->getQuantity());
        Scene::getInstance<Overworld>().getCurrentMap().removeEntity(this);
    }
}

void Item::update() {}

void Item::render() const {
    static Texture texture("Item_Overworld_Sprite.png", SDL_Rect(this->getScreenX() + 28, this->getScreenY() + 28, 24, 24));

    // update the texture's position
    texture.setX(this->getScreenX() + 28);
    texture.setY(this->getScreenY() + 28);

    texture.render();
}

Item::operator bool() const {
    return this->quantity > 0;
}
