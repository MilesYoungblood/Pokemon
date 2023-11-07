//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

class VoltTackle : public Move {
private:
    const static int MAX_PP = 24;
    bool paralysisState = false;

public:
    VoltTackle() : Move(15) {}

    explicit VoltTackle(const int currentPP) : VoltTackle() {
        if (currentPP < 0) {
            this->fillToMax();
        }
        else {
            this->setPP(currentPP);
        }
    }

    void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool & /*skip*/) override {
        // damage will be negative if the attack misses
        if (damage > 0) {
            defendingPokemon.takeDamage(damage);
            attackingPokemon.takeDamage(static_cast<int>(lround(damage / 3.0)));

            //FIXME faint Pokemon if necessary
            if (attackingPokemon.isFainted()) {

            }

            this->paralysisState = generateInteger(1, 10) == 1 and defendingPokemon.getStatus() == Status::NONE;
            if (this->paralysisState) {
                defendingPokemon.setStatus(Status::PARALYSIS);
            }
        }

        this->use();
    }

    void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const int damage, const bool  /*skipTurn*/, const bool criticalHit, const double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Volt Tackle! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            if (typeEff == 0.0) {
                printMessage("It doesn't affect " + defendingPokemon.getName() + "...");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else {
                printMessage("Volt Tackle did " + std::to_string(damage) + " damage! ");
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

                if (this->paralysisState) {
                    printMessage(defendingPokemon.getName() + " became paralyzed! ");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }

                printMessage(attackingPokemon.getName() + " took " + std::to_string(static_cast<int>(lround(damage / 3.0))) + " damage!");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

    [[nodiscard]] Type getType() const override {
        return Type::ELECTRIC;
    }

    [[nodiscard]] Move::Category getCategory() const override {
        return Move::Category::PHYSICAL;
    }

    [[nodiscard]] Move::ID getID() const override {
        return Move::ID::VOLT_TACKLE;
    }

    [[nodiscard]] std::string getName() const override {
        return "Volt Tackle";
    }

    [[nodiscard]] const char *getDescription() const override {
        return "The user electrifies itself, then charges. It causes considerable damage to the user and may leave the target with paralysis.";
    }
};
