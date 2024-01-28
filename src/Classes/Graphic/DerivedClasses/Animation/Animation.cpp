//
// Created by Miles on 11/29/2023.
//

#include "Animation.h"

Animation::Animation(const char *path) {
    const auto data = TextureManager::getInstance().loadTextureData(path);
    this->spriteSheet = std::get<0>(data);
    this->numRows = std::get<1>(data) / Constants::TILE_SIZE;
    this->numCols = std::get<2>(data) / Constants::TILE_SIZE;
}

Animation &Animation::operator=(Animation &&rhs) noexcept {
    this->numRows = rhs.numRows;
    this->numCols = rhs.numCols;
    this->spriteSheet = rhs.spriteSheet;
    rhs.spriteSheet = nullptr;

    return *this;
}

Animation::~Animation() {
    SDL_DestroyTexture(this->spriteSheet);
}

void Animation::update() {
    ++this->currentFrame;

    if (this->currentFrame == this->numCols) {
        this->currentFrame = 0;

        ++this->currentRow;
        if (this->currentRow == this->numRows) {
            this->currentRow = 0;
        }
    }
}

void Animation::render(const SDL_Rect &destRect) const {
    TextureManager::getInstance().drawFrame(this->spriteSheet, destRect, this->currentFrame, this->currentRow);
}
