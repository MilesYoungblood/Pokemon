//
// Created by Miles Youngblood on 2/22/2024.
//

#pragma once

#include "../../Rectangle.h"

class Button : public Rectangle {
private:
    std::string text;

    void (*onClick)(){ nullptr };

public:
    Button(SDL_Rect dest, SDL_Color fg, int borderSize, std::string label, void (*f)());

    void click();
};
