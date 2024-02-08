//
// Created by Miles on 12/15/2023.
//

#include "Rectangle.h"

void Rectangle::renderBox() const {
    TextureManager::getInstance().drawRect(this->dest, this->fg, this->bg, this->borderSize);
}

void Rectangle::setDest(SDL_Rect newDest) {
    this->dest = newDest;
}

SDL_Rect Rectangle::getDest() const {
    return this->dest;
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

Rectangle::Rectangle(SDL_Rect dest, SDL_Color bg, int borderSize)
        : dest(dest), fg(Constants::Color::WHITE), bg(bg), borderSize(borderSize) {}

Rectangle::Rectangle(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize)
        : dest(dest), fg(fg), bg(bg), borderSize(borderSize) {}
