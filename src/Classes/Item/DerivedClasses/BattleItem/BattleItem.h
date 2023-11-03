//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct BattleItem : public Item {
    explicit BattleItem(int quantity);

    [[nodiscard]] virtual Stat getStat() const = 0;

    [[nodiscard]] ItemID getID() const override = 0;

    [[nodiscard]] ItemType getType() const override;
};
