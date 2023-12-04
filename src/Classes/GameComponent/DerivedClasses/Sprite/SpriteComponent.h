//
// Created by Miles Youngblood on 11/17/2023.
//

#pragma once

#include "../../../TextureManager/TextureManager.h"
#include "../../GameComponent.h"

class SpriteComponent : public GameComponent {
private:
    const int NUM_FRAMES;
    const int NUM_ROWS;

    int currentFrame{ 0 };
    int currentRow{ 0 };

    SDL_Texture *sprite{ nullptr };

public:
    SpriteComponent(const char *path, int numFrames, int numRows);

    SpriteComponent(const SpriteComponent &) = delete;

    SpriteComponent(SpriteComponent &&) noexcept = delete;

    SpriteComponent &operator=(const SpriteComponent &) = delete;

    SpriteComponent &operator=(SpriteComponent &&rhs) noexcept = delete;

    ~SpriteComponent() override;

    void update();

    void render(const SDL_Rect &destRect);
};
