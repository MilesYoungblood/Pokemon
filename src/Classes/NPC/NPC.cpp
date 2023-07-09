//
// Created by Miles Youngblood on 7/7/2023.
//

#include "NPC.h"

NPC::NPC(const std::initializer_list<Pokemon> &pokemon, int x, int y, int range) : Trainer(pokemon, x, y) {
    this->range = range;
    this->defeated = false;
}

bool NPC::isInRange(const Trainer &p) {
    if (this->isFacingNorth()) {
        return p.getX() == this->x and p.getY() < this->y and p.getY() >= this->y - this->range;
    }
    else if (this->isFacingEast()) {
        return p.getY() == this->y and p.getX() > this->x and p.getX() <= this->x + this->range;
    }
    else if (this->isFacingSouth()) {
        return p.getX() == this->x and p.getY() > this->y and p.getY() <= this->y + this->range;
    }
    else if (this->isFacingWest()) {
        return p.getY() == this->y and p.getX() < this->x and p.getX() >= this->x + this->range;
    }
    else {
        return false;
    }
}

bool NPC::isDefeated() const {
    return this->defeated;
}

void NPC::defeat() {
    this->defeated = true;
}