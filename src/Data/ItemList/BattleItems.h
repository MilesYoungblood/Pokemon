//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/DerivedClasses/BattleItem/BattleItem.h"

struct XAttack : public BattleItem {
    explicit XAttack(int n) : BattleItem(n) {}

    [[nodiscard]] std::string getName() const override {
        return "X Attack";
    }

    [[nodiscard]] Stat getStat() const override {
        return Stat::ATTACK;
    }

    [[nodiscard]] ItemID getID() const override {
        return ItemID::X_ATTACK;
    }
};

struct XDefense : public BattleItem {
    explicit XDefense(int n) : BattleItem(n) {}

    [[nodiscard]] std::string getName() const override {
        return "X Defense";
    }

    [[nodiscard]] Stat getStat() const override {
        return Stat::DEFENSE;
    }

    [[nodiscard]] ItemID getID() const override {
        return ItemID::X_DEFENSE;
    }
};

struct XSpAttack : public BattleItem {
    explicit XSpAttack(int n) : BattleItem(n) {}

    [[nodiscard]] std::string getName() const override {
        return "X Sp. Attack";
    }

    [[nodiscard]] Stat getStat() const override {
        return Stat::SP_ATTACK;
    }

    [[nodiscard]] ItemID getID() const override {
        return ItemID::X_SP_ATTACK;
    }
};

struct XSpDefense : public BattleItem {
    explicit XSpDefense(int n) : BattleItem(n) {}

    [[nodiscard]] std::string getName() const override {
        return "X Sp. Defense";
    }

    [[nodiscard]] Stat getStat() const override {
        return Stat::SP_DEFENSE;
    }

    [[nodiscard]] ItemID getID() const override {
        return ItemID::X_SP_DEFENSE;
    }
};

struct XSpeed : public BattleItem {
    explicit XSpeed(int n) : BattleItem(n) {}

    [[nodiscard]] std::string getName() const override {
        return "X Speed";
    }

    [[nodiscard]] Stat getStat() const override {
        return Stat::SPEED;
    }

    [[nodiscard]] ItemID getID() const override {
        return ItemID::X_SPEED;
    }
};

struct XAccuracy : public BattleItem {
    explicit XAccuracy(int n) : BattleItem(n) {}

    [[nodiscard]] std::string getName() const override {
        return "X Accuracy";
    }

    [[nodiscard]] Stat getStat() const override {
        return Stat::ACCURACY;
    }

    [[nodiscard]] ItemID getID() const override {
        return ItemID::X_ACCURACY;
    }
};
