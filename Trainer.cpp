//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer() {
    faintCount = 0;
}

Trainer::Trainer(const std::initializer_list<Pokemon> &pokemon) {
    faintCount = 0;
    for (const auto &p : pokemon) {
        if (party.size() < MAX_POKEMON) {
            party.push_back(p);
        }
        else {
            break;
        }
    }
}

int Trainer::partySize() const {
    return static_cast<int>(party.size());
}

Item& Trainer::getItem(int item) {
    return items[item];
}

void Trainer::incFaintCount() {
    ++faintCount;
}

void Trainer::decFaintCount() {
    --faintCount;
}

Pokemon& Trainer::operator[](int spot)  {
    return party[spot];
}

const Pokemon& Trainer::operator[](int spot) const {
    return party[spot];
}

bool Trainer::canFight() {
    return faintCount < party.size();
}