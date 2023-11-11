//
// Created by Miles on 10/6/2023.
//

#pragma once

class Extrasensory : public Move {
private:
    const static int MAX_PP = 32;       // FIXME likely incorrect

public:
    Extrasensory() : Move(30) {}

    explicit Extrasensory(const int currentPP) : Extrasensory() {
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

        skip = generateInteger(1, 10) == 1;
    }

    void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const int damage, const bool skipTurn, const bool criticalHit, const double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Extrasensory! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            printMessage("Extrasensory did " + std::to_string(damage) + " damage! ");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            if (typeEff == 0.0) {
                printMessage("It doesn't affect " + defendingPokemon.getName() + "...");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else if (typeEff >= 2.0) {
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
        return 80;
    }

    [[nodiscard]] Type getType() const override {
        return Type::PSYCHIC;
    }

    [[nodiscard]] Move::Category getCategory() const override {
        return Move::Category::SPECIAL;
    }

    [[nodiscard]] Move::Id getId() const override {
        return Move::Id::EXTRASENSORY;
    }

    [[nodiscard]] std::string getName() const override {
        return "Extrasensory";
    }

    [[nodiscard]] const char *getDescription() const override {
        return "The user attacks with an odd, unseeable power. It may also make the target flinch.";
    }
};
