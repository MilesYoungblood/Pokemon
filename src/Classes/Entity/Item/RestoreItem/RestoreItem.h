//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../Item.h"

struct RestoreItem final : Item {
    RestoreItem(const char *id, int quantity);

    [[nodiscard]] std::size_t getClass() const override;

    [[nodiscard]] int getAmount() const;

    [[nodiscard]] bool isHp() const;

    void restore(Pokemon &pokemon) const;

    void restore(Move &move) const;

    [[nodiscard]] std::string restoreMessage(const Pokemon &pokemon) const;

    [[nodiscard]] std::string restoreMessage(const Move &move) const;
};
