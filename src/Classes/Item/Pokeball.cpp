//
// Created by Miles on 18/05/2023.
//

#include "Pokeball.h"

PokeBall::PokeBall() : Item() { this->catchRate = 0.00f; }
PokeBall::PokeBall(int quantity, float catchRate, const char * name) : Item(quantity, name) { this->catchRate = catchRate; }

float PokeBall::getCatchRate() const { return this->catchRate; }