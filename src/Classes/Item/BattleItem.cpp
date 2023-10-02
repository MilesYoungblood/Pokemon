//
// Created by Miles on 18/05/2023.
//

#include "BattleItem.h"

BattleItem::BattleItem() : Item() { this->stat = Stat::NONE; }
BattleItem::BattleItem(int quantity, const char * name, Stat stat) : Item(quantity, name) { this->stat = stat; }

Stat BattleItem::getStat() const { return this->stat; }