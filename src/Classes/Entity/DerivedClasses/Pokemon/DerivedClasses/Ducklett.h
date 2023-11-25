//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Ducklett : public Pokemon {
    Ducklett() : Pokemon(1, 62, 44, 50, 44, 50, 55) {}

    Ducklett(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Ducklett";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DUCKLETT;
    }
};
