//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Tympole : public Pokemon {
    Tympole() : Pokemon(1, 50, 50, 40, 50, 40, 64) {}

    Tympole(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Tympole";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TYMPOLE;
    }
};

