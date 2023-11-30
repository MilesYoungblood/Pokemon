//
// Created by Miles on 11/29/2023.
//

#include "Animation.h"

Animation::Animation(const char *path, int numFrames, int numRows)
        : spriteSheet(TextureManager::getInstance().loadTexture(path)), numFrames(numFrames), numRows(numRows) {}

Animation &Animation::operator=(Animation &&rhs) noexcept {
    this->numFrames = rhs.numFrames;
    this->numRows = rhs.numRows;
    this->spriteSheet = rhs.spriteSheet;
    rhs.spriteSheet = nullptr;

    return *this;
}

Animation::~Animation() {
    SDL_DestroyTexture(this->spriteSheet);
}

void Animation::update() {
    ++this->currentFrame;

    if (this->currentFrame == this->numFrames) {
        this->currentFrame = 0;

        ++this->currentRow;
        if (this->currentRow == this->numRows) {
            this->currentRow = 0;
        }
    }
}

void Animation::render(const SDL_Rect &destRect) {
    TextureManager::getInstance().drawFrame(this->spriteSheet, destRect, this->currentFrame, this->currentRow);
}
