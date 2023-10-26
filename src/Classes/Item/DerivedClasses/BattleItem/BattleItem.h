//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

class BattleItem : public Item {
private:
    const Stat stat;

public:
    BattleItem(const char *name, int quantity, Stat stat);

    [[nodiscard]] Stat getStat() const override;
    [[nodiscard]] ItemID getID() const override = 0;
    [[nodiscard]] ItemType getType() const override;

    void restore(Pokemon &pokemon) override;
    void restore(Move &move) override;
    void restoreMessage(const Pokemon &pokemon) override;
    void restoreMessage(const Move &move) override;
    bool catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) override;
};
