//
// Created by Miles on 12/8/2023.
//

#include "TimedVisual.h"

TimedVisual::TimedVisual(const char *path, int frames, SDL_Rect dest) : Texture(path, dest), numFrames(frames) {}

void TimedVisual::update() {
    if (this->counter == this->numFrames) {
        this->deactivate();
    }
    else {
        ++this->counter;
    }
}
