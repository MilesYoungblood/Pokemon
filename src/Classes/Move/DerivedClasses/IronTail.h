//
// Created by Miles Youngblood on 6/15/2023.
//

#pragma once

class IronTail : public Move {
private:
    const static int MAX_PP = 24;
    bool loweredState = false;

public:
    IronTail() : Move(15) {}

    explicit IronTail(const int currentPP) : IronTail() {
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

            //FIXME redo calculations
            this->loweredState = generateInteger(1, 10) == 1 and defendingPokemon.getSpDefense() > -6;

            //FIXME account for limit reached
            if (this->loweredState) {
                defendingPokemon.lowerDefense(1);
            }
        }

        this->use();
    }

    void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const int damage, const bool  /*skipTurn*/, const bool criticalHit, const double typeEff) override {
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

    [[nodiscard]] int getPower() const override {
        return 100;
    }

    [[nodiscard]] int getAccuracy() const override {
        return 75;
    }

    [[nodiscard]] Type getType() const override {
        return Type::STEEL;
    }

    [[nodiscard]] Category getCategory() const override {
        return Category::PHYSICAL;
    }

    [[nodiscard]] MoveID getID() const override {
        return MoveID::IRON_TAIL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Iron Tail";
    }

    [[nodiscard]] const char *getDescription() const override {
        return "The target is slammed with a steel-hard tail. It may also lower the target’s Defense stat.";
    }
};
