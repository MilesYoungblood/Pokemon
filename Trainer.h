//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include <stdexcept>
#include "Pokemon.h"
#include "Items.h"

enum {MAX_POKEMON = 6, MAX_ITEMS = 100};

class Trainer {
private:
    std::array<Pokemon, MAX_POKEMON> party;
    std::array<Items, MAX_ITEMS> items;

    int faintCount;
public:
    Trainer();
    void setParty(const std::initializer_list<Pokemon> &list) {
        for (auto &p : list) {
            party[0] = p;
        }
    }

    Pokemon& getPokemon(int);
    std::array<Pokemon, MAX_POKEMON> getParty();
    Items& getItem(int);

    int numFainted() const;
};