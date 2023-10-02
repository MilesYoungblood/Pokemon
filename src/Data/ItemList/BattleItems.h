//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/BattleItem.h"

struct XAttack : public BattleItem {
    explicit XAttack(int quantity) : BattleItem(quantity, "X-Attack", Stat::ATTACK) {}
};

struct XSpeed : public BattleItem {
    explicit XSpeed(int quantity) : BattleItem(quantity, "X-Speed", Stat::SPEED) {}
};