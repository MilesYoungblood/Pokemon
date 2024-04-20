//
// Created by Miles Youngblood on 4/14/2024.
//

#include "Sprite.h"

int Component::Sprite::getCurrentRow() const {
    return this->currentRow;
}

int Component::Sprite::getCurrentCol() const {
    return this->currentCol;
}

void Component::Sprite::update(const int numRows, const int numCols) {
    ++this->currentCol;

    if (this->currentCol == numCols) {
        this->currentCol = 0;
        ++this->currentRow;

        if (this->currentRow == numRows) {
            this->currentRow = 0;
        }
    }
}
