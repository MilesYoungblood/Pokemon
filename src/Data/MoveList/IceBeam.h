//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

struct IceBeam : public Move {
    bool freezeState = false;

    IceBeam() : Move("Ice Beam", Type::ICE, Category::SPECIAL, 10, 90, 100) {}

    void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.setHP(defendingPokemon.getHP() - damage);


            this->freezeState = Move::generateInteger(1, 10) == 1 and defendingPokemon.getStatus() == Status::NONE;
            if (this->freezeState)
                defendingPokemon.setStatus(Status::FREEZE);
        }

        --this->pp;
    }

    void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage,bool criticalHit, double typeEff) override {
        Move::printMessage(attackingPokemon.getName() + " used Ice Beam! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            Move::printMessage("Thunder did " + std::to_string(damage) + " damage! ");
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

            if (this->freezeState) {
                Move::printMessage(defendingPokemon.getName() + " became frozen!");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            Move::printMessage(defendingPokemon.getName() + " avoided the attack!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        Move::printMessage('\n', 0);
        std::cout.flush();

        this->freezeState = false;
    }

    //TODO add message
};