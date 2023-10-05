//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

struct Thunder : public Move {
    bool paralysisState = false;

    Thunder() : Move("Thunder", 10, 110, 70, Type::ELECTRIC, Category::SPECIAL) {}

    void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.setHP(defendingPokemon.getHP() - damage);

            this->paralysisState = generateInteger(1, 10) == 1 and defendingPokemon.getStatus() == Status::NONE;
            if (this->paralysisState)
                defendingPokemon.setStatus(Status::PARALYSIS);
        }

        --this->pp;
    }

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Thunder! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            if (typeEff == 0.0) {
                printMessage("It doesn't affect " + defendingPokemon.getName() + "...");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else {
                printMessage("Thunder did " + std::to_string(damage) + " damage! ");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                if (typeEff >= 2.0) {
                    printMessage("It's super effective! ");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                else if (typeEff <= 0.5) {
                    printMessage("It's not very effective... ");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }

                if (criticalHit) {
                    printMessage("A critical hit!");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }

                if (this->paralysisState) {
                    printMessage(defendingPokemon.getName() + " became paralyzed!");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
        }
        else {
            printMessage(defendingPokemon.getName() + " avoided the attack!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        printMessage('\n');
        std::cout.flush();

        this->paralysisState = false;
    }
};