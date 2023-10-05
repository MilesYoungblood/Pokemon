//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/BattleItem.h"

struct XAttack : public BattleItem {
    explicit XAttack(int n) : BattleItem("X-Attack", n, Stat::ATTACK) {}
};

struct XSpeed : public BattleItem {
    explicit XSpeed(int n) : BattleItem("X-Speed", n, Stat::SPEED) {}
};