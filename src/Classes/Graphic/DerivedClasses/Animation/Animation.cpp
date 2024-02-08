//
// Created by Miles on 11/29/2023.
//

#include "Animation.h"

Animation::Animation(const std::string &path) {
    const auto data = TextureManager::getInstance().loadTextureData(path);
    this->spriteSheet = std::get<0>(data);
    this->numRows = std::get<1>(data) / Constants::TILE_SIZE;
    this->numCols = std::get<2>(data) / Constants::TILE_SIZE;
}

Animation::Animation(Animation &&toMove) noexcept
        : numRows(toMove.numRows), numCols(toMove.numCols), spriteSheet(toMove.spriteSheet) {
    toMove.spriteSheet = nullptr;
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
    if (strlen(SDL_GetError()) > 0) {
        std::clog << "Unable to destroy sprite sheet: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
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

void Animation::render() const {}

void Animation::render(const SDL_Rect &destRect) const {
    TextureManager::getInstance().drawFrame(this->spriteSheet, destRect, this->currentFrame, this->currentRow);
}
