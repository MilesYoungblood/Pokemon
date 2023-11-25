//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Klink : public Pokemon {
    Klink() : Pokemon(1, 40, 55, 70, 45, 60, 30) {}

    Klink(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Klink";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::STEEL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 130;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::KLINK;
    }
};
