//
// Created by Miles Youngblood on 11/17/2023.
//

#pragma once

#include "../../../../Singletons/TextureManager/TextureManager.h"
#include "../../GameComponent.h"

class SpriteComponent : public GameComponent {
private:
    const int NUM_FRAMES{ 1 };
    const int NUM_ROWS{ 1 };

    int currentFrame{ 0 };
    int currentRow{ 0 };

    SDL_Texture *sprite{ nullptr };

public:
    SpriteComponent(const char *path, int numFrames, int numRows)
            : sprite(TextureManager::getInstance().loadTexture(path)), NUM_FRAMES(numFrames), NUM_ROWS(numRows) {}

    SpriteComponent(const SpriteComponent &) = delete;

    SpriteComponent(SpriteComponent &&) noexcept = delete;

    SpriteComponent &operator=(const SpriteComponent &) = delete;

    SpriteComponent &operator=(SpriteComponent &&rhs) noexcept = delete;

    SpriteComponent() override {
        SDL_DestroyTexture(this->sprite);
    }

    inline void update() override {
        ++this->currentFrame;

        if (this->currentFrame == this->NUM_FRAMES) {
            this->currentFrame = 0;

            ++this->currentRow;
            if (this->currentRow == this->NUM_ROWS) {
                this->currentRow = 0;
            }
        }
    }

    inline void render(const SDL_Rect &destRect) {
        TextureManager::getInstance().drawFrame(this->sprite, destRect, this->currentFrame, this->currentRow);
    }
};
