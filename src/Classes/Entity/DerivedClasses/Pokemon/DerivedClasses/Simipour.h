//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Simipour : public Pokemon {
    Simipour() : Pokemon(1, 75, 98, 63, 98, 63, 101) {}

    Simipour(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Simipour";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SIMIPOUR;
    }
};
