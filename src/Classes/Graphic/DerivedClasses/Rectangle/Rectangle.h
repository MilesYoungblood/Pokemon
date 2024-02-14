//
// Created by Miles on 12/15/2023.
//

#pragma once

#include "../../Graphic.h"

class Rectangle : public Graphic {
private:
    SDL_Color fg{ Constants::Color::WHITE };
    SDL_Color bg{ Constants::Color::BLACK };

    int borderSize{ 0 };

protected:
    Rectangle() = default;

    void renderBox() const;

    [[nodiscard]] SDL_Color getFg() const;

    [[nodiscard]] SDL_Color getBg() const;

    void setBorderSize(int n);

    [[nodiscard]] int getBorderSize() const;

public:
    Rectangle(SDL_Rect dest, SDL_Color bg, int borderSize);

    Rectangle(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize);

    Rectangle(const Rectangle &) = default;

    Rectangle(Rectangle &&) noexcept = default;

    Rectangle &operator=(const Rectangle &) = default;

    Rectangle &operator=(Rectangle &&) noexcept = default;

    ~Rectangle() override = default;

    void update() override = 0;

    void render() const override = 0;
};
