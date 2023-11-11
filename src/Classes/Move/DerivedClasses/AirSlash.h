//
// Created by Miles on 10/6/2023.
//

#pragma once

class AirSlash : public Move {
private:
    const static int MAX_PP = 24;

public:
    AirSlash() : Move(20) {}

    explicit AirSlash(const int currentPP) : AirSlash() {
        if (currentPP < 0) {
            this->fillToMax();
        }
        else {
            this->setPP(currentPP);
        }
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

    [[nodiscard]] int getPower() const override {
        return 75;
    }

    [[nodiscard]] int getAccuracy() const override {
        return 95;
    }

    [[nodiscard]] Type getType() const override {
        return Type::FLYING;
    }

    [[nodiscard]] Move::Category getCategory() const override {
        return Move::Category::SPECIAL;
    }

    [[nodiscard]] Move::Id getId() const override {
        return Move::Id::AIR_SLASH;
    }

    [[nodiscard]] std::string getName() const override {
        return "Air Slash";
    }

    [[nodiscard]] const char *getDescription() const override {
        return "The user attacks with a blade of air that slices even the sky. It may also make the target flinch.";
    }
};
