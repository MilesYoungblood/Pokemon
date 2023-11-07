//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

class IceBeam : public Move {
private:
    const static int MAX_PP = 16;
    bool freezeState = false;

public:
    IceBeam() : Move(10) {}

    explicit IceBeam(const int currentPP) : IceBeam() {
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

            this->freezeState = generateInteger(1, 10) == 1 and defendingPokemon.getStatus() == Status::NONE;
            if (this->freezeState) {
                defendingPokemon.setStatus(Status::FREEZE);
            }
        }

        this->use();
    }

    void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const int damage, const bool  /*skipTurn*/, const bool criticalHit, const double typeEff) override {
        printMessage(attackingPokemon.getName() + " used Ice Beam! ");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // damage will be negative if the attack misses
        if (damage > 0) {
            printMessage("Ice Beam did " + std::to_string(damage) + " damage! ");
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

            if (this->freezeState) {
                printMessage(defendingPokemon.getName() + " became frozen!");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            printMessage(defendingPokemon.getName() + " avoided the attack!");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        printMessage('\n');
        std::cout.flush();

        this->freezeState = false;
    }

    [[nodiscard]] int getPower() const override {
        return 95;
    }

    [[nodiscard]] Type getType() const override {
        return Type::ICE;
    }

    [[nodiscard]] Move::Category getCategory() const override {
        return Move::Category::SPECIAL;
    }

    [[nodiscard]] Move::ID getID() const override {
        return Move::ID::ICE_BEAM;
    }

    [[nodiscard]] std::string getName() const override {
        return "Ice Beam";
    }

    [[nodiscard]] const char *getDescription() const override {
        return "The target is struck with an icy-cold beam of energy. It may also freeze the target solid.";
    }
};
