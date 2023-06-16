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

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, float typeEff) override {
        Move::printMessage(attackingPokemon.getName() + " used Focus Blast! ");
        sleep(1);
        // damage will be negative if the attack misses
        if (damage > 0) {
            if (typeEff == 0.0f) {
                Move::printMessage("It doesn't affect " + defendingPokemon.getName() + "...");
                sleep(1);
            }
            else {
                Move::printMessage("Focus Blast did " + std::to_string(damage) + " damage! ");
                sleep(1);

                if (typeEff >= 2.0f) {
                    Move::printMessage("It's super effective! ");
                    sleep(1);
                }
                else if (typeEff <= 0.5f) {
                    Move::printMessage("It's not very effective... ");
                    sleep(1);
                }

                if (criticalHit) {
                    Move::printMessage("A critical hit!");
                    sleep(1);
                }

                if (this->loweredState) {
                    Move::printMessage(defendingPokemon.getName() + "'s special defense was lowered!");
                    sleep(1);
                }
            }
        }
        else {
            Move::printMessage(defendingPokemon.getName() + " avoided the attack!");
            sleep(1);
        }

        Move::printMessage('\n', 0);
        std::cout.flush();

        this->loweredState = false;
    }
};