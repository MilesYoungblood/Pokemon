//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer() = default;

void Trainer::setParty(const Pokemon& spot1) {
    party[0] = spot1;
}
void Trainer::setParty(const Pokemon &spot1, const Pokemon &spot2) {
    party[0] = spot1;
    party[1] = spot2;
}

void Trainer::setParty(const Pokemon &spot1, const Pokemon &spot2, const Pokemon &spot3) {
    party[0] = spot1;
    party[1] = spot2;
    party[2] = spot3;
}

void Trainer::setParty(const Pokemon &spot1, const Pokemon &spot2, const Pokemon &spot3, const Pokemon &spot4) {
    party[0] = spot1;
    party[1] = spot2;
    party[2] = spot3;
    party[3] = spot4;
}

void Trainer::setParty(const Pokemon &spot1, const Pokemon &spot2, const Pokemon &spot3, const Pokemon &spot4, const Pokemon &spot5) {
    party[0] = spot1;
    party[1] = spot2;
    party[2] = spot3;
    party[3] = spot4;
    party[4] = spot5;
}

void Trainer::setParty(const Pokemon &spot1, const Pokemon &spot2, const Pokemon &spot3, const Pokemon &spot4, const Pokemon &spot5, const Pokemon &spot6) {
    party[0] = spot1;
    party[1] = spot2;
    party[2] = spot3;
    party[3] = spot4;
    party[4] = spot5;
    party[5] = spot6;
}

Pokemon& Trainer::getPokemon(int pokemon) {
    return party[pokemon];
}

Items& Trainer::getItem(int item) {
    return items[item];
}