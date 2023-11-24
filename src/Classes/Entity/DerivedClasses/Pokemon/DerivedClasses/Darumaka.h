//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Darumaka : public Pokemon {
    Darumaka() : Pokemon(1, 70, 90, 45, 15, 45, 50) {}

    Darumaka(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Darumaka";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIRE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DARUMAKA;
    }
};
