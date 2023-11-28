//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

class BattleItem : public Item {
public:
    enum class Id {
        X_ATTACK,
        X_DEFENSE,
        X_SP_ATTACK,
        X_SP_DEFENSE,
        X_SPEED,
        X_ACCURACY
    };

    struct Data {
        std::string_view name;
        Pokemon::Stat stat;
    };

    BattleItem(BattleItem::Id id, int quantity) : Item(quantity), id(id) {
        if (BattleItem::nameFunction == nullptr) {
            throw std::runtime_error("Tried constructing a Battle Item without initializing class\n");
        }
    }

    static void initName(std::string (*instructions)(BattleItem::Id)) {
        BattleItem::nameFunction = instructions;
    }

    static void initStat(Pokemon::Stat (*instructions)(BattleItem::Id)) {
        BattleItem::statFunction = instructions;
    }

    [[nodiscard]] std::string getName() const override {
        return BattleItem::nameFunction(this->id);
    }

    [[nodiscard]] Pokemon::Stat getStat() const {
        return BattleItem::statFunction(this->id);
    }

    [[nodiscard]] BattleItem::Id getId() const {
        return this->id;
    }

    [[nodiscard]] Item::Class getClass() const override {
        return Item::Class::BATTLE;
    }

private:
    BattleItem::Id id;

    inline static std::string (*nameFunction)(BattleItem::Id){ nullptr };

    inline static Pokemon::Stat (*statFunction)(BattleItem::Id){ nullptr };
};
