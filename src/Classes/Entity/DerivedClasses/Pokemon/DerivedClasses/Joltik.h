//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Joltik : public Pokemon {
    Joltik() : Pokemon(1, 50, 47, 50, 57, 50, 65) {}

    Joltik(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Joltik";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::ELECTRIC;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::JOLTIK;
    }
};
