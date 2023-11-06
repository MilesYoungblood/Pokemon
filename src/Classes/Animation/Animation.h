//
// Created by Miles on 11/5/2023.
//

#pragma once

#include "../../Singletons/TextureManager/TextureManager.h"

class Animation {
private:
    const int NUM_FRAMES;
    const int NUM_ROWS;

    int currentFrame{ 0 };
    int currentRow{ 0 };

    SDL_Texture *spriteSheet;

public:
    explicit Animation(SDL_Texture *spriteSheet, int numFrames, int numRows)
            : spriteSheet(spriteSheet), NUM_FRAMES(numFrames), NUM_ROWS(numRows) {}

    Animation(const Animation &) = delete;

    Animation(const Animation &&) = delete;

    Animation &operator=(const Animation &) = delete;

    Animation &operator=(const Animation &&) = delete;

    ~Animation() {
        SDL_DestroyTexture(this->spriteSheet);
    }

    inline void update() {
        ++this->currentFrame;

        if (this->currentFrame == this->NUM_FRAMES) {
            this->currentFrame = 0;

            ++this->currentRow;
            if (this->currentRow == this->NUM_ROWS) {
                this->currentRow = 0;
            }
        }
    }

    inline void draw(const SDL_Rect &destRect) {
        TextureManager::getInstance()->drawFrame(this->spriteSheet, destRect, this->currentFrame, this->currentRow);
    }
};
