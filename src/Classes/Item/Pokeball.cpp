//
// Created by Miles on 18/05/2023.
//

#include "Pokeball.h"

PokeBall::PokeBall(int quantity, double catchRate, const char * name) : Item(quantity, name) { this->catchRate = catchRate; }

PokeBall::PokeBall(int quantity) : PokeBall(quantity, 1.0, "Poke Ball") {}
double PokeBall::getCatchRate() const { return this->catchRate; }