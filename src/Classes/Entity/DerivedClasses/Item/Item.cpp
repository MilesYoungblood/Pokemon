//
// Created by miles on 5/25/2022.
//

#include "../../../../Functions/GeneralFunctions.h"
#include "../../../Singleton/DerivedClasses/Scene/DerivedClasses/Overworld/Overworld.h"
#include "../../../Singleton/DerivedClasses/TextureManager/TextureManager.h"
#include "../../../Singleton/DerivedClasses/GraphicsEngine/GraphicsEngine.h"
#include "../../../Singleton/DerivedClasses/Mixer/Mixer.h"
#include "../../../Singleton/DerivedClasses/KeyManager/KeyManager.h"
#include "../Character/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "Item.h"

Item::Item(const int n) : Entity(0, 0), quantity(n) {}

Item::Item(const int n, const int x, const int y) : Entity(x, y), quantity(n) {}

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

std::string Item::getKey() const {
    return "Item";
}

void Item::interact() {
    if (not GraphicsEngine::getInstance().hasAny<TextBox>()) {
        ++entitiesUpdating;
        KeyManager::getInstance().lock(SDL_SCANCODE_RETURN);

        Player::getPlayer().setState(Character::State::IMMOBILE);
        Overworld::createTextBox(
                "You obtained a" + std::string(isVowel(this->getName()[0]) ? "n " : " ") + this->getName() + '!'
        );
        Mix_PauseMusic();
        Mixer::getInstance().playSound("item_found");
        Mix_ChannelFinished([](int) -> void {
            KeyManager::getInstance().unlock(SDL_SCANCODE_RETURN);
            Mix_ResumeMusic();
            --entitiesUpdating;
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

constexpr int DIMENSION = Map::TILE_SIZE * 3 / 10;
constexpr int OFFSET = (Map::TILE_SIZE - DIMENSION) / 2;

void Item::render(SDL_Texture *sprite) const {
    TextureManager::getInstance().draw(
        sprite,
        SDL_Rect(this->getScreenPosition().getX() + OFFSET, this->getScreenPosition().getY() + DIMENSION, DIMENSION, DIMENSION)
    );
}

bool Item::canUse() const {
    return this->quantity > 0;
}
