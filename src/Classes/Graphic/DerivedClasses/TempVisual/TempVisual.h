//
// Created by Miles on 12/8/2023.
//

#pragma once

#include "../../Graphic.h"

class TempVisual : public Graphic {
private:
    SDL_Texture *visual;
    SDL_Rect rect;

    int counter{ 0 };

    int numFrames;

public:
    TempVisual(const char *path, int frames, SDL_Rect dest);

    TempVisual(const TempVisual &) = default;

    TempVisual(TempVisual &&) noexcept = default;

    TempVisual &operator=(const TempVisual &) = default;

    TempVisual &operator=(TempVisual &&) noexcept = default;

    ~TempVisual() override;

    void update() override;

    void render() const override;
};
