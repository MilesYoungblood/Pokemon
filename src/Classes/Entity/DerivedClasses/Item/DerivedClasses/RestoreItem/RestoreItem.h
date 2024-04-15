//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct RestoreItem : Item {
    explicit RestoreItem(int quantity);

    [[nodiscard]] std::string getName() const override = 0;

    [[nodiscard]] std::string getEffect() const override = 0;

    [[nodiscard]] std::size_t getClass() const override;

    [[nodiscard]] virtual int getAmount() const = 0;

    [[nodiscard]] virtual bool isHp() const = 0;

    void restore(Pokemon &pokemon) const;

    virtual void restore(Move &move) const;

    [[nodiscard]] std::string restoreMessage(const Pokemon &pokemon) const;

    [[nodiscard]] std::string restoreMessage(const Move &move) const;
};
