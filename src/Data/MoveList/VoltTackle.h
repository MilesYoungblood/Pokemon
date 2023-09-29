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
            attackingPokemon.setHP(attackingPokemon.getHP() - static_cast<int>(lround(damage * 0.3)));

            //FIXME faint pokemon if necessary

            this->paralysisState = Move::generateInteger(1, 10) == 1 and defendingPokemon.getStatus() != "paralysis";
            if (this->paralysisState)
                defendingPokemon.setStatus("paralysis");
        }

        --this->pp;
    }

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, double typeEff) override {
        Move::printMessage(attackingPokemon.getName() + " used Volt Tackle! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            if (typeEff == 0.0) {
                Move::printMessage("It doesn't affect " + defendingPokemon.getName() + "...");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else {
                Move::printMessage("Volt Tackle did " + std::to_string(damage) + " damage! ");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                if (typeEff >= 2.0) {
                    Move::printMessage("It's super effective! ");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                else if (typeEff <= 0.5) {
                    Move::printMessage("It's not very effective... ");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }

                if (criticalHit) {
                    Move::printMessage("A critical hit! ");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }

                if (this->paralysisState) {
                    Move::printMessage(defendingPokemon.getName() + " became paralyzed! ");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }

                Move::printMessage(attackingPokemon.getName() + " took " + std::to_string(static_cast<int>(lround(damage * 0.3))) + " damage!");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            Move::printMessage(defendingPokemon.getName() + " avoided the attack!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        Move::printMessage('\n', 0);
        std::cout.flush();

        this->paralysisState = false;
    }
};