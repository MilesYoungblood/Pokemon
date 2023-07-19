//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

struct Thunder : public Move {
    bool paralysisState = false;

    Thunder() : Move("Thunder", "electric", "special", 10, 110, 70) {}

    void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.setHP(defendingPokemon.getHP() - damage);

            this->paralysisState = Move::generateInteger(1, 10) == 1 and defendingPokemon.getStatus() != "paralysis";
            if (this->paralysisState)
                defendingPokemon.setStatus("paralysis");
        }

        --this->pp;
    }

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, double typeEff) override {
        Move::printMessage(attackingPokemon.getName() + " used Thunder! ");
        Sleep(1000);
        // damage will be negative if the attack misses
        if (damage > 0) {
            if (typeEff == 0.0) {
                Move::printMessage("It doesn't affect " + defendingPokemon.getName() + "...");
                Sleep(1000);
            }
            else {
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
                    Move::printMessage("A critical hit!");
                    Sleep(1000);
                }

                if (this->paralysisState) {
                    Move::printMessage(defendingPokemon.getName() + " became paralyzed!");
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

        this->paralysisState = false;
    }
};