//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Escavalier : public Pokemon {
    Escavalier() : Pokemon(1, 70, 135, 105, 60, 105, 20) {}

    Escavalier(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Escavalier";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::STEEL;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ESCAVALIER;
    }
};
