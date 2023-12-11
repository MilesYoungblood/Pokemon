//
// Created by Miles on 12/8/2023.
//

#pragma once

#include "../../Graphic.h"

class Visual : public Graphic {
private:
    SDL_Texture *visual;
    SDL_Rect rect;

    int counter{ 0 };

    const int NUM_FRAMES;

public:
    Visual(const char *path, int frames, SDL_Rect dest);

    ~Visual() override;

    void update() override;

    void render() const override;
};
