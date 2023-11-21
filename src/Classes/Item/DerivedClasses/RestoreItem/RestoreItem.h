//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct RestoreItem : public Item {
    RestoreItem() = default;

    explicit RestoreItem(int quantity);

    [[nodiscard]] virtual int getAmount() const = 0;

    [[nodiscard]] virtual bool isHp() const = 0;

    [[nodiscard]] Item::Id getId() const override = 0;

    [[nodiscard]] Item::Class getClass() const override;

    void restore(Pokemon &pokemon) const;

    virtual void restore(Move &move) const;

    void restoreMessage(const Pokemon &pokemon) const;

    void restoreMessage(const Move &move) const;
};
