//
// Created by Miles Youngblood on 12/5/2023.
//

#include "Graphic.h"

Graphic::Graphic(SDL_Rect rect) : dest(rect) {}

void Graphic::setDest(SDL_Rect newDest) {
    this->dest = newDest;
}

SDL_Rect Graphic::getDest() const {
    return this->dest;
}

void Graphic::deactivate() {
    this->active = false;
}

bool Graphic::isActive() const {
    return this->active;
}
