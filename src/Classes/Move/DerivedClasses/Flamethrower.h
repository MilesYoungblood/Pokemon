//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

class Flamethrower : public Move {
private:
    const static int MAX_PP = 24;
    bool burnState = false;

public:
    Flamethrower() : Move(15) {}

    explicit Flamethrower(const int currentPP) : Flamethrower() {
        if (currentPP < 0) {
            this->fillToMax();
        }
        else {
            this->setPP(currentPP);
        }
    }

    void action(Pokemon & /*attackingPokemon*/, Pokemon &defendingPokemon, int damage, bool & /*skip*/) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.takeDamage(damage);

            this->burnState = generateInteger(1, 10) == 1 and defendingPokemon.getStatus() == Status::NONE;
            if (this->burnState) {
                defendingPokemon.setStatus(Status::BURN);
            }
        }

        this->use();
    }

    void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const int damage, const bool  /*skipTurn*/, const bool criticalHit, const double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Flamethrower! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            printMessage("Flamethrower did " + std::to_string(damage) + " damage! ");
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

            if (this->burnState) {
                printMessage(defendingPokemon.getName() + " was burned!");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            printMessage(defendingPokemon.getName() + " avoided the attack!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        printMessage('\n');
        std::cout.flush();

        this->burnState = false;
    }

    [[nodiscard]] int getPower() const override {
        return 95;
    }

    [[nodiscard]] Type getType() const override {
        return Type::FIRE;
    }

    [[nodiscard]] Move::Category getCategory() const override {
        return Move::Category::SPECIAL;
    }

    [[nodiscard]] Move::ID getID() const override {
        return Move::ID::FLAMETHROWER;
    }

    [[nodiscard]] std::string getName() const override {
        return "Flamethrower";
    }

    [[nodiscard]] const char *getDescription() const override {
        return "The target is scorched with an intense blast of fire. It may also leave the target with a burn.";
    }
};
