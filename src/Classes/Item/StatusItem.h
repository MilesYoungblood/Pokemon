//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class StatusItem : public Item {
private:
    Status status;

public:
    StatusItem(const char *name, int quantity, Status status);

    [[nodiscard]] auto getStatus() const -> Status override;

    void restore(Pokemon &pokemon) override;
    void restore(Move &move) override;
    void restoreMessage(const Pokemon &pokemon) override;
    void restoreMessage(const Move &move) override;
    bool catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) override;
};
