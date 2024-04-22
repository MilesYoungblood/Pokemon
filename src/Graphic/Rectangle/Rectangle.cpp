//
// Created by Miles on 12/15/2023.
//

#include "../../Singleton/TextureManager/TextureManager.h"
#include "Rectangle.h"

Rectangle::Rectangle(const SDL_Rect dest, const int borderSize) : Graphic(dest), borderSize(borderSize) {}

Rectangle::Rectangle(const SDL_Rect dest, const SDL_Color fg, const int borderSize)
        : Graphic(dest), fg(fg), bg(Constants::Color::BLACK), borderSize(borderSize) {}

Rectangle::Rectangle(const SDL_Rect dest, const SDL_Color fg, const SDL_Color bg, const int borderSize)
        : Graphic(dest), fg(fg), bg(bg), borderSize(borderSize) {}

void Rectangle::setBorderSize(const int pt) {
    this->borderSize = pt;
}

void Rectangle::update() {
}

void Rectangle::render() const {
    TextureManager::getInstance().drawRect(this->getDest(), this->fg, this->bg, this->borderSize);
}

SDL_Color Rectangle::getFg() const {
    return this->fg;
}

SDL_Color Rectangle::getBg() const {
    return this->bg;
}

int Rectangle::getBorderSize() const {
    return this->borderSize;
}
