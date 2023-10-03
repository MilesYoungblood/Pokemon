//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer(const std::vector<Pokemon*> &pokemon, int x, int y) : Entity(x, y), party(), items(), numItems() {
    this->numFainted = 0;
    this->numPokemon= 0;

    for (const auto &p : pokemon) {
        if (this->numPokemon == Trainer::MAX_POKEMON) {
            break;
        }

        this->party[this->numPokemon] = p;
        ++this->numPokemon;
    }
}

Trainer::~Trainer() {
    for (int i = 0; i < this->numPokemon; ++i) {
        delete this->party[i];
    }

    for (int i = 0; i < Trainer::NUM_ITEM_TYPES; ++i) {
        for (int j = 0; j < this->numItems[i]; ++j) {
            delete items[i][j];
        }
    }
}

int Trainer::partySize() const {
    return this->numPokemon;
}

int Trainer::getNumItems(int type) {
    return this->numItems[type];
}

Item& Trainer::getItem(int type, int item) {
    return *this->items[type][item];
}

void Trainer::addPokemon(Pokemon *toAdd) {
    if (this->numPokemon == Trainer::MAX_POKEMON) {
        return;
    }

    this->party[this->numPokemon] = toAdd;
    ++this->numPokemon;
}

__attribute__((unused)) void Trainer::setItems(const std::vector<std::vector<Item*>> &inventory) {
    for (int i = 0; i < Trainer::NUM_ITEM_TYPES; ++i) {
        for (int j = 0; j < Trainer::MAX_ITEMS; ++j) {
            this->items[i][j] = inventory[i][j];
            ++this->numItems[i];
        }
    }
}
void Trainer::setRestoreItems(const std::vector<Item *> &inventory) {
    for (int i = 0; i < inventory.size(); ++i) {
        if (this->numItems[0] == Trainer::MAX_ITEMS) {
            break;
        }

        this->items[0][i] = inventory[i];
        ++this->numItems[0];
    }
}
void Trainer::setStatusItems(const std::vector<Item *> &inventory) {
    for (int i = 0; i < inventory.size(); ++i) {
        if (this->numItems[1] == Trainer::MAX_ITEMS) {
            break;
        }

        this->items[1][i] = inventory[i];
        ++this->numItems[1];
    }
}
void Trainer::setPokeBalls(const std::vector<Item *> &inventory) {
    for (int i = 0; i < inventory.size(); ++i) {
        if (this->numItems[2] == Trainer::MAX_ITEMS) {
            break;
        }

        this->items[2][i] = inventory[i];
        ++this->numItems[2];
    }
}
void Trainer::setBattleItems(const std::vector<Item *> &inventory) {
    for (int i = 0; i < inventory.size(); ++i) {
        if (this->numItems[3] == Trainer::MAX_ITEMS) {
            break;
        }

        this->items[3][i] = inventory[i];
        ++this->numItems[3];
    }
}

void Trainer::incFaintCount() {
    ++this->numFainted;
}

void Trainer::decFaintCount() {
    --this->numFainted;
}

void Trainer::swapPokemon(int first, int second) {
    Pokemon * copy = this->party[first];
    this->party[first] = this->party[second];
    this->party[second] = copy;
}

void Trainer::defeat() {}

Pokemon& Trainer::operator[](int spot)  {
    if (5 < spot or spot < 0)
        throw std::runtime_error("Index out of bounds");

    return *this->party[spot];
}

const Pokemon& Trainer::operator[](int spot) const {
    if (5 < spot or spot < 0)
        throw std::runtime_error("Index out of bounds");

    return *this->party[spot];
}

Trainer::operator bool() const {
    return this->numFainted < this->numPokemon;
}
