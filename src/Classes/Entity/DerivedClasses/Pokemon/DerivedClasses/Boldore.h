//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Boldore : public Pokemon {
    Boldore() : Pokemon(25, 70, 105, 105, 50, 40, 20) {}

    Boldore(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Boldore";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ROCK : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::BOLDORE;
    }
};
