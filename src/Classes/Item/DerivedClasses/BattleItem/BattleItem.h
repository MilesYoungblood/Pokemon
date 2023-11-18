//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct BattleItem : public Item {
    explicit BattleItem(int quantity) : Item(quantity) {}

    [[nodiscard]] virtual Stat getStat() const = 0;

    [[nodiscard]] Item::Id getId() const override = 0;

    [[nodiscard]] Item::Class getClass() const override {
        return Item::Class::BATTLE;
    }
};
