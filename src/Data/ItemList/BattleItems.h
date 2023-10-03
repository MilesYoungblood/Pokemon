//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/BattleItem.h"

struct XAttack : public BattleItem {
    explicit XAttack(int n) : BattleItem(n, "X-Attack", Stat::ATTACK) {}
};

struct XSpeed : public BattleItem {
    explicit XSpeed(int n) : BattleItem(n, "X-Speed", Stat::SPEED) {}
};