//
// Created by Miles Youngblood on 6/15/2023.
//

#pragma once

struct IronTail : public Move {
    bool loweredState = false;

    IronTail() : Move("Iron Tail", 15, 100, 75, Type::STEEL, Category::PHYSICAL) {}

    MoveID getID() override {
        return MoveID::IRON_TAIL;
    }

    void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool &skip) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.takeDamage(damage);

            //FIXME redo calculations
            this->loweredState = generateInteger(1, 10) == 1 and defendingPokemon.getSpDefense() > -6;

            //FIXME account for limit reached
            if (this->loweredState)
                defendingPokemon.lowerDefense(1);
        }

        --this->pp;
    }

    void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, int damage, bool skipTurn, bool criticalHit, double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Iron Tail! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            printMessage("Iron Tail did " + std::to_string(damage) + " damage! ");
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
                printMessage(defendingPokemon.getName() + "'s defense was lowered!");
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