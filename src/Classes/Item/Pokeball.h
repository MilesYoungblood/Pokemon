//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class PokeBall : public Item {
private:
    float catchRate;

public:
    PokeBall();
    PokeBall(int quantity, float catchRate, const std::string &name);

    float getCatchRate() const;
};