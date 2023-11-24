//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Yamask : public Pokemon {
    Yamask() : Pokemon(1, 38, 30, 85, 55, 65, 30) {}

    Yamask(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Yamask";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GHOST : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::YAMASK;
    }
};
