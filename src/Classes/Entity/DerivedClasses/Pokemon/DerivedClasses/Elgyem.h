//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Elgyem : public Pokemon {
    Elgyem() : Pokemon(1, 55, 55, 55, 85, 55, 30) {}

    Elgyem(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Elgyem";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ELGYEM;
    }
};
