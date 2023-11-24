//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Lillipup : public Pokemon {
    Lillipup() : Pokemon(1, 45, 60, 45, 25, 45, 55) {}

    Lillipup(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Lillipup";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::LILLIPUP;
    }
};
