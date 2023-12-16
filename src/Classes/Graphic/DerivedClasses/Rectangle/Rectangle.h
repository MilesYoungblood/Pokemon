//
// Created by Miles on 12/15/2023.
//

#pragma once

#include "../../Graphic.h"

class Rectangle : public Graphic {
private:
    SDL_Rect dest;

    SDL_Color fg;
    SDL_Color bg;

    int borderSize;

public:
    Rectangle(SDL_Rect dest, SDL_Color bg, int borderSize);

    Rectangle(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize);

    Rectangle(const Rectangle &) = default;

    Rectangle(Rectangle &&) noexcept = default;

    Rectangle &operator=(const Rectangle &) = default;

    Rectangle &operator=(Rectangle &&) noexcept = default;

    ~Rectangle() override = default;

    void update() override;

    void render() const override;
};
