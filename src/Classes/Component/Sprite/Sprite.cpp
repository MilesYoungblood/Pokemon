//
// Created by Miles Youngblood on 4/14/2024.
//

#include "Sprite.h"

int Project::Sprite::getCurrentRow() const {
    return this->currentRow;
}

int Project::Sprite::getCurrentCol() const {
    return this->currentCol;
}

void Project::Sprite::update(const int numRows, const int numCols) {
    ++this->currentCol;

    if (this->currentCol == numCols) {
        this->currentCol = 0;
        ++this->currentRow;

        if (this->currentRow == numRows) {
            this->currentRow = 0;
        }
    }
}
