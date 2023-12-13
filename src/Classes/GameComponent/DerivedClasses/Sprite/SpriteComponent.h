//
// Created by Miles Youngblood on 11/17/2023.
//

#pragma once

#include "../../../Singleton/DerivedClasses/TextureManager/TextureManager.h"
#include "../../GameComponent.h"

class SpriteComponent : public GameComponent {
private:
    Uint32 numRows;
    Uint32 numCols;

    int currentFrame{ 0 };
    int currentRow{ 0 };

    SDL_Texture *sprite{ nullptr };

public:
    explicit SpriteComponent(const char *path);

    SpriteComponent(const SpriteComponent &) = delete;

    SpriteComponent(SpriteComponent &&) noexcept = delete;

    SpriteComponent &operator=(const SpriteComponent &) = delete;

    SpriteComponent &operator=(SpriteComponent &&rhs) noexcept = delete;

    ~SpriteComponent() override;

    void update();

    void render(const SDL_Rect &destRect);
};
