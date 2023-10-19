//
// Created by Miles on 18/05/2023.
//

#include "BattleItem.h"

BattleItem::BattleItem(const char *name, const int quantity, const Stat stat) : Item(name, quantity) { this->stat = stat; }

Stat BattleItem::getStat() const { return this->stat; }

void BattleItem::restore(Pokemon &pokemon) {}

void BattleItem::restore(Move &move) {}

void BattleItem::restoreMessage(const Pokemon &pokemon) {}

void BattleItem::restoreMessage(const Move &move) {}

bool BattleItem::catchPokemon(const Pokemon &pokemon, bool attempts[]) { return false; }
