//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Carracosta : public Pokemon {
    Carracosta() : Pokemon(37, 74, 108, 133, 83, 65, 32) {}

    Carracosta(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Carracosta";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::ROCK;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::CARRACOSTA;
    }
};
