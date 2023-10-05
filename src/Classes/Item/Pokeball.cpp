//
// Created by Miles on 18/05/2023.
//

#include "Pokeball.h"

PokeBall::PokeBall(const char *name, int quantity, double catchRate) : Item(name, quantity) { this->catchRate = catchRate; }

PokeBall::PokeBall(int n) : PokeBall("Poke Ball", n, 1.0) {}

void PokeBall::useMessage() {
    printMessage("You threw a");

    if (isVowel(this->name[0]))
        printMessage('n');

    printMessage(' ' + this->getName() + "! ");
}

void PokeBall::restore(Pokemon &pokemon) {}

void PokeBall::restore(Move &move) {}

void PokeBall::restoreMessage(Pokemon &pokemon) {}

void PokeBall::restoreMessage(Move &move) {}


__attribute__((unused)) double PokeBall::getCatchRate() const { return this->catchRate; }
