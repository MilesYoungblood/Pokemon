//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Dwebble : public Pokemon {
    Dwebble() : Pokemon(1, 50, 65, 85, 35, 35, 55) {}

    Dwebble(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Dwebble";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::ROCK;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DWEBBLE;
    }
};
