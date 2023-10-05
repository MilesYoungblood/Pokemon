//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

struct IceBeam : public Move {
    bool freezeState = false;

    IceBeam() : Move("Ice Beam", 10, 90, 100, Type::ICE, Category::SPECIAL) {}

    void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.setHP(defendingPokemon.getHP() - damage);

            this->freezeState = generateInteger(1, 10) == 1 and defendingPokemon.getStatus() == Status::NONE;
            if (this->freezeState)
                defendingPokemon.setStatus(Status::FREEZE);
        }

        --this->pp;
    }

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage,bool criticalHit, double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Ice Beam! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            printMessage("Ice Beam did " + std::to_string(damage) + " damage! ");
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

            if (this->freezeState) {
                printMessage(defendingPokemon.getName() + " became frozen!");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            printMessage(defendingPokemon.getName() + " avoided the attack!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        printMessage('\n');
        std::cout.flush();

        this->freezeState = false;
    }
};