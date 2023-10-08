//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class BattleItem : public Item {
private:
    Stat stat;

public:
    BattleItem(const char *name, int quantity, Stat stat);

    Stat getStat() const override;

    void restore(Pokemon &pokemon) override;
    void restore(Move &move) override;
    void restoreMessage(Pokemon &pokemon) override;
    void restoreMessage(Move &move) override;
    bool catchPokemon(const Pokemon &pokemon, bool attempts[]) override;
};