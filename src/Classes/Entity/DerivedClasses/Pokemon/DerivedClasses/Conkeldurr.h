//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Conkeldurr : public Pokemon {
    Conkeldurr() : Pokemon(25, 105, 140, 95, 55, 65, 45) {}

    Conkeldurr(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Conkeldurr";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIGHTING : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::CONKELDURR;
    }
};
