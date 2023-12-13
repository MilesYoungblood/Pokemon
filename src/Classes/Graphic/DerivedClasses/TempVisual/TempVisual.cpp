//
// Created by Miles on 12/8/2023.
//

#include "TempVisual.h"

TempVisual::TempVisual(const char *path, int frames, SDL_Rect dest)
        : visual(TextureManager::getInstance().loadTexture(path)), numFrames(frames), rect(dest) {}

TempVisual::~TempVisual() {
    SDL_DestroyTexture(this->visual);
}

void TempVisual::update() {
    if (this->counter == this->numFrames) {
        this->deactivate();
    }
    else {
        ++this->counter;
    }
}

void TempVisual::render() const {
    TextureManager::getInstance().draw(this->visual, rect);
}
