//
// Created by Miles on 12/8/2023.
//

#pragma once

#include "../../Graphic.h"

class Visual : public Graphic {
private:
    SDL_Texture *visual{ nullptr };
    SDL_Rect rect{ 0, 0, 0, 0 };

    int counter{ 0 };

    const int NUM_FRAMES;

public:
    Visual(const char *path, int frames);

    void update() override;

    void render() const override;
};
