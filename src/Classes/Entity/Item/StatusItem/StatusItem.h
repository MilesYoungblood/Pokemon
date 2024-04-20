//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../Item.h"

struct StatusItem final : Item {
    StatusItem(const char *id, int quantity);

    [[nodiscard]] std::size_t getClass() const override;

    [[nodiscard]] StatusCondition getStatus() const;

    void restore(Pokemon &pokemon) const;

    [[nodiscard]] static std::string restoreMessage(const Pokemon &pokemon) ;
};
