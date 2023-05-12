//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include "Pokemon.h"
#include "Item.h"

class Trainer {
private:
    const static int MAX_POKEMON = 6;
    const static int MAX_ITEMS = 100;
    int faintCount;

    std::string name;
    std::vector<Pokemon> party;
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

    bool canFight();
};