//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer() {
    this->numFainted = 0;
    this->numPokemon = 0;
}

Trainer::Trainer(const std::initializer_list<Pokemon> &pokemon) {
    this->numFainted = 0;
    this->numPokemon= 0;
    for (const auto &p : pokemon) {
        if (this->numPokemon + 1 == Trainer::MAX_POKEMON)
            break;

        else {
            this->party[this->numPokemon] = p;
            ++this->numPokemon;
        }
    }
}

int Trainer::partySize() const {
    return this->numPokemon;
}

Item& Trainer::getItem(int item) {
    return this->items[item];
}

void Trainer::incFaintCount() {
    ++this->numFainted;
}

void Trainer::decFaintCount() {
    --this->numFainted;
}

Pokemon& Trainer::operator[](int spot)  {
    if (5 < spot or spot < 0)
        throw std::runtime_error("Index out of bounds");

    return this->party[spot];
}

const Pokemon& Trainer::operator[](int spot) const {
    if (5 < spot or spot < 0)
        throw std::runtime_error("Index out of bounds");

    return this->party[spot];
}

bool Trainer::canFight() const {
    return this->numFainted < this->numPokemon;
}