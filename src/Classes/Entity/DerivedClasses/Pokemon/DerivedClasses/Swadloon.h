//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Swadloon : public Pokemon {
    Swadloon() : Pokemon(20, 55, 63, 90, 50, 80, 42) {}

    Swadloon(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Swadloon";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::GRASS;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SWADLOON;
    }
};
