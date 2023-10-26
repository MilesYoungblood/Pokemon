//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/DerivedClasses/BattleItem/BattleItem.h"

struct XAttack : public BattleItem {
    explicit XAttack(int n) : BattleItem("X Attack", n, Stat::ATTACK) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::X_ATTACK;
    }
};

struct XDefense : public BattleItem {
    explicit XDefense(int n) : BattleItem("X Defense", n, Stat::DEFENSE) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::X_DEFENSE;
    }
};

struct XSpAttack : public BattleItem {
    explicit XSpAttack(int n) : BattleItem("X Sp. Attack", n, Stat::SP_ATTACK) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::X_SP_ATTACK;
    }
};

struct XSpDefense : public BattleItem {
    explicit XSpDefense(int n) : BattleItem("X Sp. Defense", n, Stat::SP_DEFENSE) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::X_SP_DEFENSE;
    }
};

struct XSpeed : public BattleItem {
    explicit XSpeed(int n) : BattleItem("X Speed", n, Stat::SPEED) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::X_SPEED;
    }
};

struct XAccuracy : public BattleItem {
    explicit XAccuracy(int n) : BattleItem("X Accuracy", n, Stat::ACCURACY) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::X_ACCURACY;
    }
};
