//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class PokeBall : public Item {
protected:
    double catchRate;
    PokeBall(int n, double catchRate, const char * name);

public:
    explicit PokeBall(int n);

    double getCatchRate() const;
};