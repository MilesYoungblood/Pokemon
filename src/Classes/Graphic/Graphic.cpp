//
// Created by Miles Youngblood on 12/5/2023.
//

#include "Graphic.h"

Graphic::Graphic(const SDL_Rect dest) : dest(dest) {}

void Graphic::setDest(const SDL_Rect newDest) {
    this->dest = newDest;
}

void Graphic::setX(const int x) {
    this->dest.x = x;
}

void Graphic::setY(const int y) {
    this->dest.y = y;
}

void Graphic::setW(const int w) {
    this->dest.w = w;
}

void Graphic::setH(const int h) {
    this->dest.h = h;
}

SDL_Rect Graphic::getDest() const {
    return this->dest;
}

int Graphic::getX() const {
    return this->dest.x;
}

int Graphic::getY() const {
    return this->dest.y;
}

int Graphic::getW() const {
    return this->dest.w;
}

int Graphic::getH() const {
    return this->dest.h;
}

void Graphic::deactivate() {
    this->active = false;
}

bool Graphic::isActive() const {
    return this->active;
}
