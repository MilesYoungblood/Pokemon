//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Timburr : public Pokemon {
    Timburr() : Pokemon(1, 75, 80, 55, 25, 35, 35) {}

    Timburr(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Timburr";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIGHTING : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 180;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TIMBURR;
    }
};

