//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer() {
    faintCount = 0;
}

Pokemon& Trainer::getPokemon(int pokemon) {
    return party[pokemon];
}

std::array<Pokemon, MAX_POKEMON> Trainer::getParty() {
    return party;
}

Items& Trainer::getItem(int item) {
    return items[item];
}

int Trainer::numFainted() const {
    return faintCount;
}
