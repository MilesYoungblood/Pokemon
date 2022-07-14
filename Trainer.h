//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include "Pokemon.h"
#include "Items.h"

enum {MAX_POKEMON = 6};

class Trainer {
private:
    std::array<Pokemon, MAX_POKEMON> party;
    std::array<Items, 100> items;
public:
    Trainer();

    void setParty(const Pokemon&);
    void setParty(const Pokemon&, const Pokemon&);
    void setParty(const Pokemon&, const Pokemon&, const Pokemon&);
    void setParty(const Pokemon&, const Pokemon&, const Pokemon&, const Pokemon&);
    void setParty(const Pokemon&, const Pokemon&, const Pokemon&, const Pokemon&, const Pokemon&);
    void setParty(const Pokemon&, const Pokemon&, const Pokemon&, const Pokemon&, const Pokemon&, const Pokemon&);

    Pokemon& getPokemon(int);
    Items& getItem(int);
};