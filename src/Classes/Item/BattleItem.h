//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class BattleItem : public Item {
private:
    Stat stat;

public:
    BattleItem(const char *name, int quantity, Stat stat);

    [[nodiscard]] auto getStat() const -> Stat override;

    void restore(Pokemon &pokemon) override;
    void restore(Move &move) override;
    void restoreMessage(const Pokemon &pokemon) override;
    void restoreMessage(const Move &move) override;
    auto catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) -> bool override;
};
