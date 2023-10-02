//
// Created by Miles Youngblood on 7/7/2023.
//

#include "NPC.h"

NPC::NPC(const std::vector<Pokemon*> &pokemon, int x, int y, int range) : Trainer(pokemon, x, y) {
    this->range = range;
    this->canBattle = true;
}

NPC::NPC(const NPC &toCopy) : Trainer(toCopy) {
    this->canBattle = toCopy.canBattle;
}

NPC::~NPC() {
    for (auto &type : this->items) {
        for (auto &item : type) {
            delete item;
        }
    }
}

NPC& NPC::operator=(const NPC &rhs) {
    if (this != &rhs) {
        this->numFainted = rhs.numFainted;
        this->numPokemon = rhs.numPokemon;
        this->x = rhs.x;
        this->y = rhs.y;
        this->range = rhs.range;
        this->direction = rhs.direction;
        this->model = rhs.model;
        this->canBattle = rhs.canBattle;

        for (int i = 0; i < this->numPokemon; ++i) {
            delete this->party[i];
        }
        for (int i = 0; i < rhs.numPokemon; ++i) {
            this->party[i] = rhs.party[i];
        }

        for (auto &item : this->items) {
            for (auto &j : item) {
                delete j;
            }
        }
        for (int i = 0; i < Trainer::NUM_ITEM_TYPES; ++i) {
            for (int j = 0; j < Trainer::MAX_ITEMS; ++j) {
                this->items[i][j] = rhs.items[i][j];
            }
        }
    }
    return *this;
}

NPC::operator bool() const {
    return this->canBattle;
}

/*
bool NPC::canFight() const {
    return this->canBattle;
}
 */

void NPC::defeat() {
    this->canBattle = false;
}