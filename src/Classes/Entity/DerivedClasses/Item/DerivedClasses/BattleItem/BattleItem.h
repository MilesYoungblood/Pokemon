//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct BattleItem final : Item {
    BattleItem(const char *id, int quantity);

    void boost(Pokemon &pokemon, int amount, bool &limit) const;

    [[nodiscard]] std::string boostMessage(const Pokemon &pokemon, int amount, bool limit) const;

    [[nodiscard]] std::size_t getClass() const override;

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] std::string getStat() const;
};
