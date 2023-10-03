//
// Created by Miles on 18/05/2023.
//

#include "Pokeball.h"

PokeBall::PokeBall(int n, double catchRate, const char * name) : Item(n, name) { this->catchRate = catchRate; }

PokeBall::PokeBall(int n) : PokeBall(n, 1.0, "Poke Ball") {}
double PokeBall::getCatchRate() const { return this->catchRate; }