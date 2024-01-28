//
// Created by Miles on 12/8/2023.
//

#include "TimedVisual.h"

TimedVisual::TimedVisual(const char *path, int frames, SDL_Rect dest)
        : visual(TextureManager::getInstance().loadTexture(path)), numFrames(frames), rect(dest) {}

TimedVisual::~TimedVisual() {
    SDL_DestroyTexture(this->visual);
}

void TimedVisual::update() {
    if (this->counter == this->numFrames) {
        this->deactivate();
    }
    else {
        ++this->counter;
    }
}

void TimedVisual::render() const {
    TextureManager::getInstance().draw(this->visual, rect);
}
