//
// Created by miles on 5/25/2022.
//

#include "Item.h"
#include "../../../Graphic/DerivedClasses/Texture/Texture.h"

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
