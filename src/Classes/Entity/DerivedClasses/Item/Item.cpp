//
// Created by miles on 5/25/2022.
//

#include "../../../Singleton/DerivedClasses/TextureManager/TextureManager.h"
#include "Item.h"

Item::Item(int n) : quantity(n) {}

Item::Item(int n, int x, int y) : Entity(x, y), quantity(n) {}

void Item::init() {
    Item::texture = TextureManager::getInstance().loadTexture("Item_Overworld_Sprite.png");
}

void Item::clean() {
    if (Item::texture != nullptr) {
        SDL_DestroyTexture(Item::texture);
        if (strlen(SDL_GetError()) > 0) {
            std::clog << "Unable to destroy Item texture: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }
}

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
    std::string message{ "You used a" };

    if (isVowel(this->getName()[0])) {
        message += 'n';
    }

    return message.append(' ' + this->getName() + '!');
}

std::string Item::noEffectMessage(const Pokemon &pokemon) const {
    return this->getName() + " had no effect on " + pokemon.getName() + ".\n";
}

void Item::interact() {

}

void Item::update() {}

void Item::render() const {
    TextureManager::getInstance().draw(
            Item::texture,
            SDL_Rect(
                    this->getScreenX() + 28,
                    this->getScreenY() + 28,
                    24,
                    24
            )
    );
}

Item::operator bool() const {
    return this->quantity > 0;
}
