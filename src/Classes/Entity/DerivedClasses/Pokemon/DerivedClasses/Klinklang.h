//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Klinklang : public Pokemon {
    Klinklang() : Pokemon(49, 60, 100, 115, 70, 85, 90) {}

    Klinklang(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Klinklang";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::STEEL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 30;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::KLINKLANG;
    }
};
