//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

class RestoreItem : public Item {
private:
    const int amount;
    const RestoreType restoreType;

public:
    RestoreItem(const char *name, int quantity, int amount, RestoreType restoreType);

    [[nodiscard]] int getAmount() const override;
    [[nodiscard]] RestoreType getRestoreType() const override;
    [[nodiscard]] ItemType getType() const override;

    void restore(Pokemon &pokemon) override;
    void restore(Move &move) override;
    void restoreMessage(const Pokemon &pokemon) override;
    void restoreMessage(const Move &move) override;
    bool catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) override;
};
