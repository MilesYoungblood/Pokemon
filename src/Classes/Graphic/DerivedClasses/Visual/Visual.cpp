//
// Created by Miles on 12/8/2023.
//

#include "Visual.h"

Visual::Visual(const char *path, int frames) : visual(TextureManager::getInstance().loadTexture(path)),
                                               NUM_FRAMES(frames) {}

void Visual::update() {
    if (this->counter == this->NUM_FRAMES) {
        this->deactivate();
    }
    else {
        ++this->counter;
    }
}

void Visual::render() const {
    TextureManager::getInstance().draw(this->visual, rect);
}
