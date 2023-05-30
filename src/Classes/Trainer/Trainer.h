//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include "../Pokemon/Pokemon.h"
#include "../Item/Item.h"
#include "../Item/RestoreItem.h"
#include "../Item/StatusItem.h"
#include "../Item/Pokeball.h"
#include "../Item/BattleItem.h"

class Trainer {
private:
    const static int MAX_POKEMON = 6;   // max number of Pokemon per party
    const static int MAX_ITEMS = 100;   // max number of items per bag
    int numFainted;                     // number of fainted Pokemon
    int numPokemon;                     // current number of Pokemon in party

    std::string name;
    std::array<Pokemon, MAX_POKEMON> party;
    std::array<Item, MAX_ITEMS> items;

public:
    Trainer();
    Trainer(const std::initializer_list<Pokemon> &pokemon);

    int partySize() const;
    Item& getItem(int item);

    void incFaintCount();
    void decFaintCount();

    Pokemon& operator[](int spot);
    const Pokemon& operator[](int spot) const;

    bool canFight() const;
};