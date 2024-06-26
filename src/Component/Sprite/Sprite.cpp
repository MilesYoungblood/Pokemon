//
// Created by Miles Youngblood on 4/14/2024.
//

#include "Sprite.h"

Component::Sprite::Sprite(const int frameSpeed, const int numCols, const int numRows)
        : frameSpeed(std::max(1, frameSpeed)), numCols(std::max(1, numCols)), numRows(std::max(1, numRows)) {}

int Component::Sprite::getCurrentElapsed() const {
    return this->framesElapsed;
}

int Component::Sprite::getCurrentCol() const {
    return this->currentCol;
}

int Component::Sprite::getFrameSpeed() const {
    return this->frameSpeed;
}

int Component::Sprite::getNumCols() const {
    return this->numCols;
}

void Component::Sprite::update() {
    // every frame, we increase the elapsed frames
    ++this->framesElapsed;

    // if the elapsed frames reaches the frame speed, we can update
    if (this->framesElapsed == this->frameSpeed) {
        ++this->currentCol;
        this->framesElapsed = 0;

        if (this->currentCol == this->numCols) {
            this->currentRow = (this->currentRow + 1) % this->numRows;
            this->currentCol = 0;
        }
    }
}
