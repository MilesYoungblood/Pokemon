//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include <stdexcept>
#include "Pokemon.h"
#include "Item.h"

class Trainer {
private:
    enum {MAX_POKEMON = 6, MAX_ITEMS = 100};
    std::vector<Pokemon> party;
    std::array<Item, MAX_ITEMS> items;
    int faintCount;

public:
    Trainer();
    Trainer(const std::initializer_list<Pokemon> &);

    int partySize() const;
    Item& getItem(int);

    int numFainted() const;

    void incFaintCount();
    void decFaintCount();

    Pokemon& operator[](int);
    const Pokemon& operator[](int) const;
};