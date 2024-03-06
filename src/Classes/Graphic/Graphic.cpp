//
// Created by Miles Youngblood on 12/5/2023.
//

#include "Graphic.h"

Graphic::Graphic(SDL_Rect dest) : dest(dest) {}

void Graphic::setDest(SDL_Rect newDest) {
    this->dest = newDest;
}

void Graphic::setX(int x) {
    this->dest.x = x;
}

void Graphic::setY(int y) {
    this->dest.y = y;
}

void Graphic::setW(int w) {
    this->dest.w = w;
}

void Graphic::setH(int h) {
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
