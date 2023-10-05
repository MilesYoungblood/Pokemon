//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

struct FlashCannon : public Move {
    bool loweredState = false;

    FlashCannon() : Move("Flash Cannon", 10, 80, 100, Type::STEEL, Category::SPECIAL) {}

    void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.setHP(defendingPokemon.getHP() - damage);

            //FIXME redo calculations
            this->loweredState = generateInteger(1, 10) == 1 and defendingPokemon.getSpDefense() > -6;

            if (this->loweredState)
                defendingPokemon.setSpDefense(defendingPokemon.getSpDefense() - 1);
        }

        --this->pp;
    }

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Flash Cannon! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            printMessage("Flash Cannon did " + std::to_string(damage) + " damage! ");
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
                printMessage("A critical hit! ");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            if (this->loweredState) {
                printMessage(defendingPokemon.getName() + "'s special defense was lowered!");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            printMessage(defendingPokemon.getName() + " avoided the attack!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        printMessage('\n');
        std::cout.flush();

        this->loweredState = false;
    }
};