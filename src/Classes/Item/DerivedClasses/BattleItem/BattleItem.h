//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct BattleItem : public Item {
    enum class Id {
        X_ATTACK,
        X_DEFENSE,
        X_SP_ATTACK,
        X_SP_DEFENSE,
        X_SPEED,
        X_ACCURACY
    };

    explicit BattleItem(int quantity);

    void boost(Pokemon &pokemon, int amount, bool &limit) const;

    [[nodiscard]] std::string boostMessage(const Pokemon &pokemon, int amount, bool limit) const;

    [[nodiscard]] std::string getName() const override = 0;

    [[nodiscard]] std::string getEffect() const override = 0;

    [[nodiscard]] virtual Pokemon::Stat getStat() const = 0;

    [[nodiscard]] virtual BattleItem::Id getId() const = 0;

    [[nodiscard]] Item::Class getClass() const override;
};

inline std::mutex battleItemMutex;
inline std::unordered_map<BattleItem::Id, std::unique_ptr<BattleItem>(*)(int)> battleItems;
