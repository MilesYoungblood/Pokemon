//
// Created by Miles Youngblood on 12/3/2023.
//

#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const char *path, int numFrames, int numRows)
        : sprite(TextureManager::getInstance().loadTexture(path)), NUM_FRAMES(numFrames), NUM_ROWS(numRows) {}

SpriteComponent::~SpriteComponent() {
    SDL_DestroyTexture(this->sprite);
}

void SpriteComponent::update() {
    ++this->currentFrame;

    if (this->currentFrame == this->NUM_FRAMES) {
        this->currentFrame = 0;

        ++this->currentRow;
        if (this->currentRow == this->NUM_ROWS) {
            this->currentRow = 0;
        }
    }
}

void SpriteComponent::render(const SDL_Rect &destRect) {
    TextureManager::getInstance().drawFrame(this->sprite, destRect, this->currentFrame, this->currentRow);
}
