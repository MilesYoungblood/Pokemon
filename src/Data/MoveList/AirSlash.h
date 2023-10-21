//
// Created by Miles on 10/6/2023.
//

#pragma once

struct AirSlash : public Move {
    AirSlash() : Move("Air Slash", 15, 75, 95, Type::FLYING, Category::SPECIAL) {}

    auto getID() -> MoveID override {
        return MoveID::AIR_SLASH;
    }

    void action(Pokemon & /*attackingPokemon*/, Pokemon &defendingPokemon, int damage, bool &skip) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.takeDamage(damage);
        }

        this->use();

        skip = generateInteger(1, 100) <= 30;
    }

    void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const int damage, const bool skipTurn, const bool criticalHit, const double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Air Slash! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            printMessage("Air Slash did " + std::to_string(damage) + " damage! ");
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

            if (skipTurn) {
                printMessage(defendingPokemon.getName() + " flinched!");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            printMessage(defendingPokemon.getName() + " avoided the attack!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        printMessage('\n');
        std::cout.flush();
    }
};
