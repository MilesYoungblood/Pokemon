//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Blitzle : public Pokemon {
    Blitzle() : Pokemon(1, 45, 60, 32, 50, 32, 76) {}

    Blitzle(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Blitzle";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::BLITZLE;
    }
};
