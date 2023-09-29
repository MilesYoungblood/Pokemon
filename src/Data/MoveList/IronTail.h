//
// Created by Miles Youngblood on 6/15/2023.
//

#pragma once

struct IronTail : public Move {
    bool loweredState = false;

    IronTail() : Move("Iron Tail", "steel", "physical", 15, 100, 75) {}

    void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.setHP(defendingPokemon.getHP() - damage);

            //FIXME redo calculations
            this->loweredState = Move::generateInteger(1, 10) == 1 and defendingPokemon.getSpDefense() > -6;

            if (this->loweredState)
                defendingPokemon.setDefense(defendingPokemon.getDefense() - 1);
        }

        --this->pp;
    }

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, double typeEff) override {
        Move::printMessage(attackingPokemon.getName() + " used Iron Tail! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            Move::printMessage("Iron Tail did " + std::to_string(damage) + " damage! ");
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

            if (this->loweredState) {
                Move::printMessage(defendingPokemon.getName() + "'s defense was lowered!");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            Move::printMessage(defendingPokemon.getName() + " avoided the attack!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        Move::printMessage('\n', 0);
        std::cout.flush();

        this->loweredState = false;
    }
};