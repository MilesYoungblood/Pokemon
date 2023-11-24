//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Venipede : public Pokemon {
    Venipede() : Pokemon(1, 30, 45, 59, 30, 39, 57) {}

    Venipede(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Venipede";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::POISON;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::VENIPEDE;
    }
};
