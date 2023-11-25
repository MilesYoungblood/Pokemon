//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Archen : public Pokemon {
    Archen() : Pokemon(1, 55, 112, 45, 74, 45, 70) {}

    Archen(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Archen";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ROCK : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ARCHEN;
    }
};
