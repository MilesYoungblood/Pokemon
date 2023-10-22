//
// Created by Miles on 18/05/2023.
//

#include "BattleItem.h"

BattleItem::BattleItem(const char *name, const int quantity, const Stat stat) : Item(name, quantity), stat(stat) {}

Stat BattleItem::getStat() const { return this->stat; }

void BattleItem::restore(Pokemon &pokemon) {}

void BattleItem::restore(Move &move) {}

void BattleItem::restoreMessage(const Pokemon &pokemon) {}

void BattleItem::restoreMessage(const Move &move) {}

bool BattleItem::catchPokemon(const Pokemon & /*pokemon*/, std::array<bool, 4> & /*attempts*/) { return false; }
