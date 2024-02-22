//
// Created by Miles Youngblood on 2/22/2024.
//

#include "Button.h"

Button::Button(SDL_Rect dest, SDL_Color color, int borderSize, std::string label, void (*f)())
        : Rectangle(dest, color, Constants::Color::BLACK, borderSize), text(std::move(label)), onClick(f) {}

void Button::click() {
    this->onClick();
}