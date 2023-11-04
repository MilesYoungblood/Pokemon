//
// Created by Miles on 10/6/2023.
//

#pragma once

struct DarkPulse : public Move {
private:
    const static int MAX_PP = 24;

public:
    DarkPulse() : Move(15) {}

    explicit DarkPulse(const int currentPP) : Move(currentPP) {
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

        skip = generateInteger(1, 5) == 1;
    }

    void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const int damage, const bool skipTurn, const bool criticalHit, const double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Dark Pulse! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            printMessage("Dark Pulse did " + std::to_string(damage) + " damage! ");
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
        return 80;
    }

    [[nodiscard]] Type getType() const override {
        return Type::DARK;
    }

    [[nodiscard]] Category getCategory() const override {
        return Category::SPECIAL;
    }

    [[nodiscard]] MoveID getID() const override {
        return MoveID::DARK_PULSE;
    }

    [[nodiscard]] std::string getName() const override {
        return "Dark Pulse";
    }

    [[nodiscard]] const char *getDescription() const override {
        return "The user releases a horrible aura imbued with dark thoughts. It may also make the target flinch.";
    }
};
