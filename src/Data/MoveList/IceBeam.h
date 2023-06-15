//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

struct IceBeam : public Move {
    bool freezeState = false;

    IceBeam() : Move("Ice Beam", "ice", "special", 10, 90, 100) {}

    void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.setHP(defendingPokemon.getHP() - damage);


            this->freezeState = Move::generateInteger(1, 10) == 1 and defendingPokemon.getStatus() != "freeze";
            if (this->freezeState)
                defendingPokemon.setStatus("freeze");
        }

        --this->pp;
    }

    //TODO add message
};