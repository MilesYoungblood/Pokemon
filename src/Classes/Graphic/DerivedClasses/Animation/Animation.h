//
// Created by Miles on 11/5/2023.
//

#pragma once

#include "../../Graphic.h"

class Animation : public Graphic {
private:
    Uint32 numCols{ 0 };
    Uint32 numRows{ 0 };

    int currentFrame{ 0 };
    int currentRow{ 0 };

    SDL_Texture *spriteSheet{ nullptr };

public:
    Animation() = default;

    explicit Animation(const std::string &path);

    Animation(const Animation &) = delete;

    Animation(Animation &&) noexcept;

    Animation &operator=(const Animation &) = delete;

    Animation &operator=(Animation &&rhs) noexcept;

    ~Animation() override;

    void update() override;

    // FIXME
    void render() const override;

    void render(const SDL_Rect &destRect) const;
};
