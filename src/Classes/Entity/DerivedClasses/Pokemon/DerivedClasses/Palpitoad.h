//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Palpitoad : public Pokemon {
    Palpitoad() : Pokemon(25, 75, 65, 55, 65, 55, 69) {}

    Palpitoad(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Palpitoad";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::GROUND;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PALPITOAD;
    }
};
