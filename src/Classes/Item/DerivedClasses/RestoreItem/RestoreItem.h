//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct RestoreItem : public Item {
    explicit RestoreItem(int quantity);

    [[nodiscard]] virtual int getAmount() const = 0;

    [[nodiscard]] virtual bool isHp() const = 0;

    [[nodiscard]] ItemType getType() const override;

    void restore(Pokemon &pokemon) const;

    void restore(Move &move) const;

    void restoreMessage(const Pokemon &pokemon) const;

    void restoreMessage(const Move &move) const;
};
