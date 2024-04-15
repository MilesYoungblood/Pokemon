//
// Created by Miles on 12/15/2023.
//

#pragma once

#include "../../Graphic.h"

class Rectangle : public Graphic {
public:
    Rectangle(SDL_Rect dest, int borderSize);

    Rectangle(SDL_Rect dest, SDL_Color fg, int borderSize);

    Rectangle(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize);

    Rectangle(const Rectangle &) = default;

    Rectangle(Rectangle &&) noexcept = default;

    Rectangle &operator=(const Rectangle &) = default;

    Rectangle &operator=(Rectangle &&) noexcept = default;

    ~Rectangle() override = default;

    void setBorderSize(int pt);

    void update() override = 0;

    void render() const override = 0;

protected:
    void renderBox() const;

    [[nodiscard]] SDL_Color getFg() const;

    [[nodiscard]] SDL_Color getBg() const;

    [[nodiscard]] int getBorderSize() const;

private:
    SDL_Color fg{ Constants::Color::WHITE };
    SDL_Color bg{ Constants::Color::BLACK };

    int borderSize;
};
