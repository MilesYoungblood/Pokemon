//
// Created by Miles on 18/05/2023.
//

#include "BattleItem.h"

BattleItem::BattleItem(const char *name, int quantity, Stat stat) : Item(name, quantity) { this->stat = stat; }

Stat BattleItem::getStat() const { return this->stat; }

void BattleItem::restore(Pokemon &pokemon) {}

void BattleItem::restore(Move &move) {}

void BattleItem::restoreMessage(Pokemon &pokemon) {}

void BattleItem::restoreMessage(Move &move) {}
