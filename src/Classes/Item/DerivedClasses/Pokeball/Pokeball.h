//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

class PokeBall : public Item {
private:
    const double catchRate;

protected:
    PokeBall(const char *name, int quantity, double catchRate);

public:
    explicit PokeBall(int n);

    void useMessage() override;

    void restore(Pokemon &pokemon) override;
    void restore(Move &move) override;
    void restoreMessage(const Pokemon &pokemon) override;
    void restoreMessage(const Move &move) override;
    bool catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) override;
};
