//
// Created by Miles Youngblood on 12/3/2023.
//

#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const char *path) {
    const auto data = TextureManager::getInstance().loadTextureData(path);
    this->sprite = std::get<0>(data);
    this->numRows = std::get<1>(data);
    this->numCols = std::get<2>(data);
}

SpriteComponent::~SpriteComponent() {
    SDL_DestroyTexture(this->sprite);
}

void SpriteComponent::update() {
    ++this->currentFrame;

    if (this->currentFrame == this->numCols) {
        this->currentFrame = 0;

        ++this->currentRow;
        if (this->currentRow == this->numRows) {
            this->currentRow = 0;
        }
    }
}

void SpriteComponent::render(const SDL_Rect &destRect) {
    TextureManager::getInstance().drawFrame(this->sprite, destRect, this->currentFrame, this->currentRow);
}
