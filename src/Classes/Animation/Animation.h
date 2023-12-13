//
// Created by Miles on 11/5/2023.
//

#pragma once

#include "../Singleton/DerivedClasses/TextureManager/TextureManager.h"

class Animation {
private:
    Uint32 numCols{ 0 };
    Uint32 numRows{ 0 };

    int currentFrame{ 0 };
    int currentRow{ 0 };

    SDL_Texture *spriteSheet{ nullptr };

public:
    Animation() = default;

    explicit Animation(const char *path);

    Animation(const Animation &) = delete;

    Animation(Animation &&) = delete;

    Animation &operator=(const Animation &) = delete;

    Animation &operator=(Animation &&rhs) noexcept;

    ~Animation();

    void update();

    void render(const SDL_Rect &destRect) const;
};
