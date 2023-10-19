//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/BattleItem.h"

struct XAttack : public BattleItem {
    explicit XAttack(int n) : BattleItem("X Attack", n, Stat::ATTACK) {}
};

struct XDefense : public BattleItem {
    explicit XDefense(int n) : BattleItem("X Defense", n, Stat::DEFENSE) {}
};

struct XSpAttack : public BattleItem {
    explicit XSpAttack(int n) : BattleItem("X Sp. Attack", n, Stat::SP_ATTACK) {}
};

struct XSpDefense : public BattleItem {
    explicit XSpDefense(int n) : BattleItem("X Sp. Defense", n, Stat::SP_DEFENSE) {}
};

struct XSpeed : public BattleItem {
    explicit XSpeed(int n) : BattleItem("X Speed", n, Stat::SPEED) {}
};

struct XAccuracy : public BattleItem {
    explicit XAccuracy(int n) : BattleItem("X Accuracy", n, Stat::ACCURACY) {}
};
