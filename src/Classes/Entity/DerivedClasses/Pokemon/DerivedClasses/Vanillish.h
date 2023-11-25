//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Vanillish : public Pokemon {
    Vanillish() : Pokemon(35, 51, 65, 65, 80, 75, 59) {}

    Vanillish(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Vanillish";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ICE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::VANILLISH;
    }
};
