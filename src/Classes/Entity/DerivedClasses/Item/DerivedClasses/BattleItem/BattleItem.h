//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct BattleItem : public Item {
    explicit BattleItem(int quantity);

    void boost(Pokemon &pokemon, int amount, bool &limit) const;

    [[nodiscard]] std::string boostMessage(const Pokemon &pokemon, int amount, bool limit) const;

    [[nodiscard]] std::string getName() const override = 0;

    [[nodiscard]] std::string getEffect() const override = 0;

    [[nodiscard]] virtual Pokemon::Stat getStat() const = 0;

    [[nodiscard]] Item::Class getClass() const override;
};

inline std::mutex battleItemMutex;
inline std::unordered_map<std::string, std::unique_ptr<BattleItem>(*)(int)> battleItems;
