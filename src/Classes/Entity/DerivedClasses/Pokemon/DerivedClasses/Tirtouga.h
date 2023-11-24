//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Tirtouga : public Pokemon {
    Tirtouga() : Pokemon(1, 54, 78, 103, 53, 45, 22) {}

    Tirtouga(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Tirtouga";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::ROCK;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TIRTOUGA;
    }
};
