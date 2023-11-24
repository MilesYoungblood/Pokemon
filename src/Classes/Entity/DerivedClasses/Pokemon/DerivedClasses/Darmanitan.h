//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Darmanitan : public Pokemon {
    Darmanitan() : Pokemon(35, 105, 140, 55, 30, 55, 95) {}

    Darmanitan(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Darmanitan";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIRE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DARMANITAN;
    }
};

