//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Leavanny : public Pokemon {
    Leavanny() : Pokemon(20, 75, 103, 80, 70, 80, 92) {}

    Leavanny(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Leavanny";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::GRASS;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::LEAVANNY;
    }
};
