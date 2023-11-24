//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Roggenrola : public Pokemon {
    Roggenrola() : Pokemon(1, 55, 75, 85, 25, 25, 15) {}

    Roggenrola(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Roggenrola";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ROCK : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ROGGENROLA;
    }
};
