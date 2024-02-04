//
// Created by Miles on 12/15/2023.
//

#include "Rectangle.h"

void Rectangle::renderBox() const {
    TextureManager::getInstance().drawRect(this->dest, this->fg, this->bg, this->borderSize);
}

Rectangle::Rectangle(SDL_Rect dest, SDL_Color bg, int borderSize)
        : dest(dest), fg(Constants::Color::WHITE), bg(bg), borderSize(borderSize) {}

Rectangle::Rectangle(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize)
        : dest(dest), fg(fg), bg(bg), borderSize(borderSize) {}

void Rectangle::update() {}

void Rectangle::render() const {
    this->renderBox();
}
