//
// Created by Miles Youngblood on 2/6/2024.
//

#pragma once

#include "../../Rectangle.h"

class ResourceBar : public Rectangle {
private:
    int progress;

public:
    ResourceBar(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize, int amount);

    void raise(int n);

    void lower(int n);

    void update() override;

    void render() const override;
};
