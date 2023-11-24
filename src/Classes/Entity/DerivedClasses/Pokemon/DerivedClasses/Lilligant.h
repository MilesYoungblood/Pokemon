//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Lilligant : public Pokemon {
    Lilligant() : Pokemon(1, 70, 60, 75, 110, 75, 90) {}

    Lilligant(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Lilligant";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::LILLIGANT;
    }
};
