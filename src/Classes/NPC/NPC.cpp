//
// Created by Miles Youngblood on 7/7/2023.
//

#include "NPC.h"

NPC::NPC(const std::initializer_list<Pokemon> &pokemon, int x, int y, int range) : Trainer(pokemon, x, y) {
    this->range = range;
    this->defeated = false;
}

bool NPC::isDefeated() const {
    return this->defeated;
}

void NPC::defeat() {
    this->defeated = true;
}