//
// Created by Miles on 12/15/2023.
//

#include "Rectangle.h"

void Rectangle::renderBox() const {
    TextureManager::getInstance().drawRect(this->getDest(), this->fg, this->bg, this->borderSize);
}

SDL_Color Rectangle::getFg() const {
    return this->fg;
}

SDL_Color Rectangle::getBg() const {
    return this->bg;
}

void Rectangle::setBorderSize(int n) {
    this->borderSize = n;
}

int Rectangle::getBorderSize() const {
    return this->borderSize;
}

Rectangle::Rectangle(SDL_Rect dest, int borderSize) : Graphic(dest), borderSize(borderSize) {}

Rectangle::Rectangle(SDL_Rect dest, SDL_Color fg, int borderSize)
        : Graphic(dest), fg(fg), bg(Constants::Color::BLACK), borderSize(borderSize) {}

Rectangle::Rectangle(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize)
        : Graphic(dest), fg(fg), bg(bg), borderSize(borderSize) {}
