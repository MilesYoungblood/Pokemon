//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

class Thunder : public Move {
private:
    const static int MAX_PP = 16;
    bool paralysisState = false;

public:
    Thunder() : Move(10) {}

    explicit Thunder(const int currentPP) : Thunder() {
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

            this->paralysisState = generateInteger(1, 10) == 1 and defendingPokemon.getStatus() == Status::NONE;
            if (this->paralysisState) {
                defendingPokemon.setStatus(Status::PARALYSIS);
            }
        }

        this->use();
    }

    void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const int damage, const bool  /*skipTurn*/, const bool criticalHit, const double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Thunder! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            if (typeEff == 0.0) {
                printMessage("It doesn't affect " + defendingPokemon.getName() + "...");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else {
                printMessage("Thunder did " + std::to_string(damage) + " damage! ");
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
                    printMessage("A critical hit!");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }

                if (this->paralysisState) {
                    printMessage(defendingPokemon.getName() + " became paralyzed!");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
        }
        else {
            printMessage(defendingPokemon.getName() + " avoided the attack!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        printMessage('\n');
        std::cout.flush();

        this->paralysisState = false;
    }

    [[nodiscard]] int getPower() const override {
        return 120;
    }

    [[nodiscard]] int getAccuracy() const override {
        return 70;
    }

    [[nodiscard]] Type getType() const override {
        return Type::ELECTRIC;
    }

    [[nodiscard]] Category getCategory() const override {
        return Category::SPECIAL;
    }

    [[nodiscard]] MoveID getID() const override {
        return MoveID::THUNDER;
    }

    [[nodiscard]] std::string getName() const override {
        return "Thunder";
    }

    [[nodiscard]] const char * getDescription() const override {
        return "A wicked thunderbolt is dropped on the target to inflict damage. It may also leave the target with paralysis.";
    }
};
