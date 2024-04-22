//
// Created by Miles Youngblood on 2/22/2024.
//

#pragma once

#include "../../Texture/Texture.h"
#include "../Rectangle.h"

class Button final : public Rectangle {
public:
    Button(SDL_Rect dest, SDL_Color fg, int borderSize, const std::string &label, const std::function<void()> &f);

    Button(SDL_Color fg, int borderSize, const std::function<void()> &f);

    void init(const std::string &label);

    void press() const;

    void render() const override;

private:
    Texture text;

    std::function<void()> onPress;
};
