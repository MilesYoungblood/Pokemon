//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

struct VoltTackle : public Move {
    bool paralysisState = false;

    VoltTackle() : Move("Volt Tackle", "electric", "physical", 15, 120, 100) {}

    void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.setHP(defendingPokemon.getHP() - damage);
            attackingPokemon.setHP(attackingPokemon.getHP() - static_cast<int>(damage * .30));

            this->paralysisState = Move::generateInteger(1, 10) == 1 and defendingPokemon.getStatus() != "paralysis";
            if (this->paralysisState)
                defendingPokemon.setStatus("paralysis");
        }

        --this->pp;
    }

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, float typeEff) override {
        Move::printMessage(attackingPokemon.getName() + " used Volt Tackle! ");
        sleep(1);
        // damage will be negative if the attack misses
        if (damage > 0) {
            if (typeEff == 0.0f) {
                Move::printMessage("It doesn't affect " + defendingPokemon.getName() + "...");
                sleep(1);
            }
            else {
                Move::printMessage("Volt Tackle did " + std::to_string(damage) + " damage! ");
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
                    Move::printMessage("A critical hit! ");
                    sleep(1);
                }

                if (this->paralysisState) {
                    Move::printMessage(defendingPokemon.getName() + " became paralyzed!");
                    sleep(1);
                }

                Move::printMessage(attackingPokemon.getName() + " took " + std::to_string(static_cast<int>(damage * .30)) + " damage!");
                sleep(1);
            }
        }
        else {
            Move::printMessage(defendingPokemon.getName() + " avoided the attack!");
            sleep(1);
        }

        Move::printMessage('\n', 0);
        std::cout.flush();

        this->paralysisState = false;
    }
};