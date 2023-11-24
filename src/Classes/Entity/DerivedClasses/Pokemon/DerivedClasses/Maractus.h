//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Maractus : public Pokemon {
    Maractus() : Pokemon(1, 75, 86, 67, 106, 67, 60) {}

    Maractus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Maractus";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::MARACTUS;
    }
};
