//
// Created by Miles on 11/5/2023.
//

#pragma once

#include "../../Singletons/TextureManager/TextureManager.h"

class Animation {
private:
    int numFrames{ 0 };
    int numRows{ 0 };

    int currentFrame{ 0 };
    int currentRow{ 0 };

    SDL_Texture *spriteSheet{ nullptr };

public:
    Animation() = default;

    Animation(const char *path, int numFrames, int numRows)
            : spriteSheet(TextureManager::getInstance().loadTexture(path)), numFrames(numFrames), numRows(numRows) {}

    Animation(const Animation &) = delete;

    Animation(Animation &&) = delete;

    Animation &operator=(const Animation &) = delete;

    Animation &operator=(Animation &&rhs) noexcept {
        this->numFrames = rhs.numFrames;
        this->numRows = rhs.numRows;
        this->spriteSheet = rhs.spriteSheet;
        rhs.spriteSheet = nullptr;

        return *this;
    }

    ~Animation() {
        SDL_DestroyTexture(this->spriteSheet);
    }

    inline void update() {
        ++this->currentFrame;

        if (this->currentFrame == this->numFrames) {
            this->currentFrame = 0;

            ++this->currentRow;
            if (this->currentRow == this->numRows) {
                this->currentRow = 0;
            }
        }
    }

    inline void render(const SDL_Rect &destRect) {
        TextureManager::getInstance().drawFrame(this->spriteSheet, destRect, this->currentFrame, this->currentRow);
    }
};
