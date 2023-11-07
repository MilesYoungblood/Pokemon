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

    explicit Animation(SDL_Texture *spriteSheet, int numFrames, int numRows)
            : spriteSheet(spriteSheet), numFrames(numFrames), numRows(numRows) {
        std::cout << "Default constructor called for animation\n";
    }

    Animation(const Animation &toCopy)
            : numFrames(toCopy.numFrames), numRows(toCopy.numRows), spriteSheet(toCopy.spriteSheet) {
        std::cout << "Copy constructor called for animation\n";
    };

    Animation(Animation &&toMove)

    noexcept :
            numFrames(toMove.numFrames),
            numRows(toMove
    .numRows),
    spriteSheet(toMove
    .spriteSheet) {
        std::cout << "Move constructor called for animation\n";
    }

    Animation &operator=(const Animation &rhs) {
        std::cout << "Copy assignment operator called for animation\n";
        if (this != &rhs) {
            this->numFrames = rhs.numFrames;
            this->numRows = rhs.numRows;
            SDL_DestroyTexture(this->spriteSheet);
            // TODO FIX
        }

        return *this;
    }

    Animation &operator=(Animation &&rhs)

    noexcept {
        std::cout << "Move assignment operator called for animation\n";
        if (this != &rhs) {
            this->numFrames = rhs.numFrames;
            this->numRows = rhs.numRows;
            this->spriteSheet = rhs.spriteSheet;
            rhs.spriteSheet = nullptr;
        }

        return *this;
    }

    ~Animation() {
        std::cout << "Destructor called for animation\n";
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

    inline void draw(const SDL_Rect &destRect) {
        TextureManager::getInstance().drawFrame(this->spriteSheet, destRect, this->currentFrame, this->currentRow);
    }
};
