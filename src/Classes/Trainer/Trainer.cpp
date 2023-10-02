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

Trainer::Trainer(const Trainer &toCopy) : Entity(toCopy), party(), items(), numItems() {
    this->numFainted = toCopy.numFainted;
    this->numPokemon = toCopy.numPokemon;

    for (int i = 0; i < Trainer::NUM_ITEM_TYPES; ++i) {
        this->numItems[i] = toCopy.numItems[i];
    }

    for (int i = 0; i < toCopy.numPokemon; ++i) {
        this->party[i] = toCopy.party[i];
    }

    for (int i = 0; i < Trainer::NUM_ITEM_TYPES; ++i) {
        for (int j = 0; j < Trainer::MAX_ITEMS; ++j) {
            this->items[i][j] = toCopy.items[i][j];
        }
    }
}

Trainer::~Trainer() {
    for (auto &type : this->items) {
        for (auto &item : type) {
            delete item;
        }
    }
}

Trainer& Trainer::operator=(const Trainer &rhs) {
    if (this != &rhs) {
        this->numFainted = rhs.numFainted;
        this->numPokemon = rhs.numPokemon;

        for (int i = 0; i < Trainer::NUM_ITEM_TYPES; ++i) {
            this->numItems[i] = rhs.numItems[i];
        }

        this->x = rhs.x;
        this->y = rhs.y;
        this->range = rhs.range;
        this->direction = rhs.direction;
        this->model = rhs.model;

        for (auto &pokemon : this->party) {
            delete pokemon;
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

int Trainer::partySize() const {
    return this->numPokemon;
}

int Trainer::getNumItems(int type) {
    return this->numItems[type];
}

Item& Trainer::getItem(int type, int item) {
    return *this->items[type][item];
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

/*
bool Trainer::canFight() const {
    return this->numFainted < this->numPokemon;
}
*/

Trainer::operator bool() const {
    return this->numFainted < this->numPokemon;
}
