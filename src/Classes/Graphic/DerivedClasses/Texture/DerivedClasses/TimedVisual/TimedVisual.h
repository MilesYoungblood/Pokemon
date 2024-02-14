//
// Created by Miles on 12/8/2023.
//

#pragma once

#include "../../Texture.h"

class TimedVisual : public Texture {
private:
    int counter{ 0 };

    int numFrames;

public:
    TimedVisual(const char *path, int frames, SDL_Rect dest);

    TimedVisual(const TimedVisual &) = default;

    TimedVisual(TimedVisual &&) noexcept = default;

    TimedVisual &operator=(const TimedVisual &) = default;

    TimedVisual &operator=(TimedVisual &&) noexcept = default;

    ~TimedVisual() override = default;

    void update() override;
};
