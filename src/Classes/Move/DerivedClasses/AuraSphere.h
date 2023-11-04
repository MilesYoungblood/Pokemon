//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

class AuraSphere : public Move {
private:
    const static int MAX_PP = 32;

public:
    AuraSphere() : Move(20) {}

    explicit AuraSphere(const int currentPP) : AuraSphere() {
        if (currentPP < 0) {
            this->setPP(this->getMaxPP());
        }
        else {
            this->setPP(currentPP);
        }
    }

    void action(Pokemon & /*attackingPokemon*/, Pokemon &defendingPokemon, int damage, bool & /*skip*/) override {
        // if the calculation registers as a miss, force it as a hit
        if (damage < 0) {
            damage *= -1;
        }

        defendingPokemon.takeDamage(damage);
        this->use();
    }

    [[nodiscard]] int getPower() const override {
        return 90;
    }

    [[nodiscard]] Type getType() const override {
        return Type::FIGHTING;
    }

    [[nodiscard]] Category getCategory() const override {
        return Category::SPECIAL;
    }

    [[nodiscard]] MoveID getID() const override {
        return MoveID::AURA_SPHERE;
    }

    [[nodiscard]] std::string getName() const override {
        return "Aura Sphere";
    }

    [[nodiscard]] const char *getDescription() const override {
        return "The user looses a blast of aura power from deep within its body at the target. This move is certain to hit.";
    }
};
