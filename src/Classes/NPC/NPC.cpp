//
// Created by Miles Youngblood on 7/7/2023.
//

#include "NPC.h"

NPC::NPC(const std::vector<Pokemon*> &pokemon, int x, int y, int range) : Trainer(pokemon, x, y) {
    this->range = range;
    this->canBattle = true;
}

NPC::operator bool() const {
    return this->canBattle;
}

bool NPC::canFight() const {
    return this->canBattle;
}

void NPC::setBattleStatus(bool flag) {
    this->canBattle = flag;
}

void NPC::defeat() {
    this->canBattle = false;
}