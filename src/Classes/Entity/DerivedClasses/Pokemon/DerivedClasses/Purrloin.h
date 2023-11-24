//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Purrloin : public Pokemon {
    Purrloin() : Pokemon(1, 41, 50, 37, 50, 37, 66) {}

    Purrloin(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Purrloin";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PURRLOIN;
    }
};
