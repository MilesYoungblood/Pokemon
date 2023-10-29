//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

class WaterShuriken : public Move {
private:
    const static int MAX_PP = 32;
    mutable int numHits = 0;        // number of hits landed (from 2 to 5)

public:
    WaterShuriken() : Move(20) {}

    explicit WaterShuriken(const int currentPP) : WaterShuriken() {
        if (currentPP < 0) {
            this->fillToMax();
        }
        else {
            this->setPP(currentPP);
        }
    }

    [[nodiscard]] int getDamage() const override {
        const int possibleHits = generateInteger(2, 5);
        for (int i = 0; i < possibleHits; ++i) { // determines hits and misses
            if (generateInteger(1, 100) <= this->getAccuracy()) {
                ++this->numHits;
            }
        }

        return this->getPower() * this->numHits;
    }

    void actionMessage(const Pokemon &attackingPokemon, const Pokemon & /*defendingPokemon*/, const int damage, const bool  /*skipTurn*/, const bool criticalHit, const double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Water Shuriken! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            printMessage("Water Shuriken did " + std::to_string(damage) + " damage! ");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if (typeEff >= 2.0) {
                printMessage("It's super effective! ");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else if (typeEff <= 0.5) {
                printMessage("It's not very effective... ");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            printMessage("It hit " + std::to_string(this->numHits) + " times! ");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if (criticalHit) {
                printMessage('x' + std::to_string(this->numHits) + " critical hits!");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            //printMessage(defendingPokemon.getName() + " avoided the attack!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        printMessage('\n');
        numHits = 0;
    }

    [[nodiscard]] int getPower() const override {
        return 15;
    }

    [[nodiscard]] Type getType() const override {
        return Type::WATER;
    }

    [[nodiscard]] Category getCategory() const override {
        return Category::SPECIAL;
    }

    [[nodiscard]] MoveID getID() const override {
        return MoveID::WATER_SHURIKEN;
    }

    [[nodiscard]] std::string getName() const override {
        return "Water Shuriken";
    }

    [[nodiscard]] const char * getDescription() const override {
        return "The user hits the target with throwing stars two to five times in a row. This move always goes first.";
    }

    [[nodiscard]] bool isPriority() const override {
        return true;
    }
};
