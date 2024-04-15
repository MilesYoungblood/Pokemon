//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct BattleItem : Item {
    explicit BattleItem(int quantity);

    void boost(Pokemon &pokemon, int amount, bool &limit) const;

    [[nodiscard]] std::string boostMessage(const Pokemon &pokemon, int amount, bool limit) const;

    [[nodiscard]] std::string getName() const override = 0;

    [[nodiscard]] std::string getEffect() const override = 0;

    [[nodiscard]] std::size_t getClass() const override;

    [[nodiscard]] virtual Pokemon::Stat getStat() const = 0;
};
