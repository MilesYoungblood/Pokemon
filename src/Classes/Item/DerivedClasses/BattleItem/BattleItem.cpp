//
// Created by Miles on 18/05/2023.
//

#include "BattleItem.h"

BattleItem::BattleItem(const int quantity) : Item(quantity) {}

ItemType BattleItem::getType() const { return ItemType::BATTLE; }