//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

struct FocusBlast : public Move {
    bool loweredState = false;

    FocusBlast() : Move("Focus Blast", "fighting", "special", 5, 120, 70) {}

    void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.setHP(defendingPokemon.getHP() - damage);

            this->loweredState = Move::generateInteger(1, 10) == 1 and defendingPokemon.getSpDefense() > -6;

            if (this->loweredState)
                defendingPokemon.setSpDefense(defendingPokemon.getSpDefense() - 1);
        }

        --this->pp;
    }

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, double typeEff) override {
        Move::printMessage(attackingPokemon.getName() + " used Focus Blast! ");
        Sleep(1000);
        // damage will be negative if the attack misses
        if (damage > 0) {
            if (typeEff == 0.0) {
                Move::printMessage("It doesn't affect " + defendingPokemon.getName() + "...");
                Sleep(1000);
            }
            else {
                Move::printMessage("Focus Blast did " + std::to_string(damage) + " damage! ");
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
                    Move::printMessage("A critical hit!");
                    Sleep(1000);
                }

                if (this->loweredState) {
                    Move::printMessage(defendingPokemon.getName() + "'s special defense was lowered!");
                    Sleep(1000);
                }
            }
        }
        else {
            Move::printMessage(defendingPokemon.getName() + " avoided the attack!");
            Sleep(1000);
        }

        Move::printMessage('\n', 0);
        std::cout.flush();

        this->loweredState = false;
    }
};