//
// Created by Miles Youngblood on 2/22/2024.
//

#pragma once

#include "../../Rectangle.h"

class Button : public Rectangle {
private:
    std::string text;

    std::function<void()> onPress;

public:
    Button(SDL_Rect dest, SDL_Color fg, int borderSize, std::string label, const std::function<void()> &f);

    Button(SDL_Color fg, std::string label, const std::function<void()> &f);

    void press();

    void update() override;

    void render() const override;
};
