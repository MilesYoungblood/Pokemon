//
// Created by Miles Youngblood on 2/22/2024.
//

#include "Button.h"

Button::Button(SDL_Rect dest, SDL_Color color, int borderSize, std::string label, void (*f)())
        : Rectangle(dest, color, borderSize), text(std::move(label)), onClick(f) {}

void Button::click() {
    this->onClick();
}

void Button::update() {
}

void Button::render() const {
    this->renderBox();

    int width;
    int height;
    TTF_SizeUTF8(TextureManager::getInstance().getFont(), this->text.c_str(), &width, &height);
    TextureManager::getInstance().drawBorderedText(
            this->text,
            this->getDest().x + this->getDest().w / 2 - width / 2,
            this->getDest().y + this->getDest().h / 2 - height / 2,
            2,
            Constants::Color::WHITE,
            Constants::Color::BLACK
    );
}
