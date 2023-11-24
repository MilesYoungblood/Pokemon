//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Petilil : public Pokemon {
    Petilil() : Pokemon(1, 45, 35, 50, 70, 50, 30) {}

    Petilil(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Petilil";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    Pokemon::Id getId() const override {
        return Pokemon::Id::PETILIL;
    }
};
