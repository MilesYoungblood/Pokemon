//
// Created by Miles on 11/29/2023.
//

#include "../../../../../Map/Map.h"
#include "Animation.h"

Animation::Animation(const std::string &path, SDL_Rect rect) : Texture(rect) {
    const auto data = TextureManager::getInstance().loadTextureData(path);
    this->setTexture(std::get<0>(data));
    this->numRows = std::get<1>(data) / Map::TILE_SIZE;
    this->numCols = std::get<2>(data) / Map::TILE_SIZE;
}

Animation::Animation(Animation &&toMove) noexcept
        : Texture(toMove.getTexture()), numRows(toMove.numRows), numCols(toMove.numCols) {
    toMove.setTexture(nullptr);
}

Animation &Animation::operator=(Animation &&rhs) noexcept {
    this->numRows = rhs.numRows;
    this->numCols = rhs.numCols;
    this->setTexture(rhs.getTexture());
    rhs.setTexture(nullptr);

    return *this;
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

void Animation::render() const {
    TextureManager::getInstance().drawFrame(this->getTexture(), this->getDest(), this->currentFrame, this->currentRow);
}
