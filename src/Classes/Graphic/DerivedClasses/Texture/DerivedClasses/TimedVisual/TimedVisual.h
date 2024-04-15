//
// Created by Miles on 12/8/2023.
//

#pragma once

#include "../../Texture.h"

class TimedVisual final : public Texture {
public:
    TimedVisual(const char *path, int frames, SDL_Rect dest);

    TimedVisual(const TimedVisual &) = delete;

    TimedVisual(TimedVisual &&) noexcept = default;

    TimedVisual &operator=(const TimedVisual &) = delete;

    TimedVisual &operator=(TimedVisual &&) noexcept = default;

    ~TimedVisual() override = default;

    void update() override;

private:
    int counter{ 0 };

    int numFrames;
};
