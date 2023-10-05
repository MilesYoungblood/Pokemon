//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer() : Entity(), party(), items(), numItems() {
    this->numFainted = 0;
    this->numPokemon = 0;
}

Trainer::Trainer(int x, int y) : Entity(x, y), party(), items(), numItems() {
    this->numFainted = 0;
    this->numPokemon = 0;
}

Trainer::Trainer(const std::initializer_list<Pokemon*> &pokemon, int x, int y) : Trainer(x, y) {
    for (const auto &p : pokemon) {
        if (this->numPokemon == Trainer::MAX_POKEMON) {
            break;
        }

        this->party[this->numPokemon] = p;
        ++this->numPokemon;
    }
    for (int i = this->numPokemon; i < Trainer::MAX_POKEMON; ++i) {
        this->party[i] = nullptr;
    }
}

Trainer::Trainer(const std::initializer_list<Pokemon *> &pokemon, int x, int y, int vision) : Trainer(pokemon, x, y) {
    this->vision = vision;
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

int Trainer::getNumItems(int type) const {
    return this->numItems[type];
}

Item& Trainer::getItem(int type, int item) const {
    return *this->items[type][item];
}

void Trainer::addPokemon(Pokemon *toAdd) {
    if (this->numPokemon == Trainer::MAX_POKEMON) {
        return;
    }

    this->party[this->numPokemon] = toAdd;
    ++this->numPokemon;
}

__attribute__((unused)) void Trainer::removePokemon(int index) {
    // decrement the faint count if the Pokémon we're removing is fainted
    if (this->party[index]->isFainted()) {
        --this->numFainted;
    }
    delete this->party[index];

    // shifts over the Pokémon that were after it
    for (int i = index; i < this->numPokemon; ++i) {
        this->party[i] = party[i + 1];
    }

    --this->numPokemon;
}

void Trainer::clearParty() {
    for (int i = 0; i < this->numPokemon; ++i) {
        delete this->party[i];
    }
    this->numPokemon = 0;
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

__attribute__((unused)) void Trainer::decFaintCount() {
    --this->numFainted;
}

void Trainer::swapPokemon(int first, int second) {
    Pokemon * copy = this->party[first];
    this->party[first] = this->party[second];
    this->party[second] = copy;
}

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