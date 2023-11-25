//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Klang : public Pokemon {
    Klang() : Pokemon(38, 60, 80, 95, 70, 85, 50) {}

    Klang(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Klang";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::STEEL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::KLANG;
    }
};
