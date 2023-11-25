//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Archeops : public Pokemon {
    Archeops() : Pokemon(37, 75, 140, 65, 112, 65, 110) {}

    Archeops(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Archeops";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ROCK : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ARCHEOPS;
    }
};
