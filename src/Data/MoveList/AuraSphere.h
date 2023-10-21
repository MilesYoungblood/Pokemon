//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

struct AuraSphere : public Move {
    AuraSphere() : Move("Aura Sphere", 20, 80, 100, Type::FIGHTING, Category::SPECIAL) {}

    auto getID() -> MoveID override {
        return MoveID::AURA_SPHERE;
    }

    void action(Pokemon & /*attackingPokemon*/, Pokemon &defendingPokemon, int damage, bool & /*skip*/) override {
        // if the calculation registers as a miss, force it as a hit
        if (damage < 0) {
            damage *= -1;
        }

        defendingPokemon.setHP(defendingPokemon.getHP() - damage);
        this->use();
    }
};
