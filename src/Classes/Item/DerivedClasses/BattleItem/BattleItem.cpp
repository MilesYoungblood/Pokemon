//
// Created by Miles Youngblood on 12/1/2023.
//

#include "BattleItem.h"

BattleItem::BattleItem(BattleItem::Id id, int quantity) : Item(quantity), id(id) {
    if (BattleItem::dataFunction == nullptr) {
        throw std::runtime_error("Tried constructing a Battle Item without initializing class\n");
    }
}

void BattleItem::init(BattleItem::Data (*instructions)(BattleItem::Id)) {
    BattleItem::dataFunction = instructions;
}

std::string BattleItem::getName() const {
    return std::string(BattleItem::dataFunction(this->id).name);
}

Pokemon::Stat BattleItem::getStat() const {
    return BattleItem::dataFunction(this->id).stat;
}

BattleItem::Id BattleItem::getId() const {
    return this->id;
}

Item::Class BattleItem::getClass() const {
    return Item::Class::BATTLE;
}
