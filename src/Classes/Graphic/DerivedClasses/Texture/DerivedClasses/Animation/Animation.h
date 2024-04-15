//
// Created by Miles on 11/5/2023.
//

#pragma once

#include "../../Texture.h"

class Animation final : public Texture {
public:
    Animation(const std::string &path, SDL_Rect rect);

    Animation(const Animation &) = delete;

    Animation(Animation &&) noexcept;

    Animation &operator=(const Animation &) = delete;

    Animation &operator=(Animation &&rhs) noexcept;

    ~Animation() override = default;

    void update() override;

    void render() const override;

private:
    Uint32 numCols{ 0 };
    Uint32 numRows{ 0 };

    int currentFrame{ 0 };
    int currentRow{ 0 };
};
