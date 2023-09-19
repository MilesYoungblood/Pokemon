//
// Created by Miles Youngblood on 7/7/2023.
//

#include "NPC.h"

NPC::NPC() : Trainer() {
    this->defeated = false;
}

NPC::NPC(const std::initializer_list<Pokemon> &pokemon, int x, int y, int range) : Trainer(pokemon, x, y) {
    this->range = range;
    this->defeated = false;
}

NPC::~NPC() {
    for (auto &type : items) {
        for (auto &item : type) {
            delete item;
        }
    }

    for (int i = 0; i < this->numPokemon; ++i) {
        //this->party[i].clear();
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
        this->defeated = rhs.defeated;
        for (int i = 0; i < rhs.numPokemon; ++i) {
            this->party[i] = rhs[i];
        }

        for (auto &item : this->items) {
            for (auto &j : item) {
                delete j;
            }
        }
        for (int i = 0; i < Trainer::MAX_ITEM_TYPES; ++i) {
            for (int j = 0; j < Trainer::MAX_ITEMS; ++j) {
                this->items[i][j] = rhs.items[i][j];
            }
        }
    }
    return *this;
}

bool NPC::isDefeated() const {
    return this->defeated;
}

void NPC::defeat() {
    this->defeated = true;
}