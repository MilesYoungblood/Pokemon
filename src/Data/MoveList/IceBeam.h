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

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage,bool criticalHit, double typeEff) override {
        Move::printMessage(attackingPokemon.getName() + " used Ice Beam! ");
        Sleep(1000);
        // damage will be negative if the attack misses
        if (damage > 0) {
            Move::printMessage("Thunder did " + std::to_string(damage) + " damage! ");
            Sleep(1000);

            if (typeEff >= 2.0) {
                Move::printMessage("It's super effective! ");
                Sleep(1000);
            }
            else if (typeEff <= 0.5) {
                Move::printMessage("It's not very effective... ");
                Sleep(1000);
            }

            if (criticalHit) {
                Move::printMessage("A critical hit! ");
                Sleep(1000);
            }

            if (this->freezeState) {
                Move::printMessage(defendingPokemon.getName() + " became frozen!");
                Sleep(1000);
            }
        }
        else {
            Move::printMessage(defendingPokemon.getName() + " avoided the attack!");
            Sleep(1000);
        }

        Move::printMessage('\n', 0);
        std::cout.flush();

        this->freezeState = false;
    }

    //TODO add message
};