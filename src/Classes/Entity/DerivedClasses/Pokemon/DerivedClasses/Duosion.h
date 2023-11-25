//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Duosion : public Pokemon {
    Duosion() : Pokemon(32, 65, 40, 50, 125, 60, 30) {}

    Duosion(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Duosion";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 100;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DUOSION;
    }
};
