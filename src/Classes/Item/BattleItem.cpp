//
// Created by Miles on 18/05/2023.
//

#include "BattleItem.h"

BattleItem::BattleItem() : Item() { this->stat = "No stat"; }
BattleItem::BattleItem(int quantity, const char * name, const char * stat) : Item(quantity, name) { this->stat = stat; }

std::string BattleItem::getStat() const { return this->stat; }