//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Sewaddle : public Pokemon {
    Sewaddle() : Pokemon(1, 45, 53, 70, 40, 60, 42) {}

    Sewaddle(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Sewaddle";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::GRASS;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SEWADDLE;
    }
};
