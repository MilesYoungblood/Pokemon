//
// Created by Miles Youngblood on 12/5/2023.
//

#include "Graphic.h"

void Graphic::update() {}

void Graphic::deactivate() {
    this->active = false;
}

bool Graphic::isActive() const {
    return this->active;
}
