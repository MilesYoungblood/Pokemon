//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include "Pokemon.h"
#include "Items.h"

const int MAX_POKEMON = 6;

class Trainer {
private:
    Pokemon party[MAX_POKEMON];
    Items items[100];
public:
    Trainer();

    void setParty(const Pokemon&);
    void setParty(const Pokemon&, const Pokemon&);
    void setParty(const Pokemon&, const Pokemon&, const Pokemon&);
    void setParty(const Pokemon&, const Pokemon&, const Pokemon&, const Pokemon&);
    void setParty(const Pokemon&, const Pokemon&, const Pokemon&, const Pokemon&, const Pokemon&);
    void setParty(const Pokemon&, const Pokemon&, const Pokemon&, const Pokemon&, const Pokemon&, const Pokemon&);

    Pokemon& getPokemon(int);
};