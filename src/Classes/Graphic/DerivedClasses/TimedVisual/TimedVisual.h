//
// Created by Miles on 12/8/2023.
//

#pragma once

#include "../../Graphic.h"

class TimedVisual : public Graphic {
private:
    SDL_Texture *visual;
    SDL_Rect rect;

    int counter{ 0 };

    int numFrames;

public:
    TimedVisual(const char *path, int frames, SDL_Rect dest);

    TimedVisual(const TimedVisual &) = default;

    TimedVisual(TimedVisual &&) noexcept = default;

    TimedVisual &operator=(const TimedVisual &) = default;

    TimedVisual &operator=(TimedVisual &&) noexcept = default;

    ~TimedVisual() override;

    void update() override;

    void render() const override;
};
