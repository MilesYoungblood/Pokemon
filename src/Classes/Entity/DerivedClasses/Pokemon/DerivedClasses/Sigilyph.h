//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Sigilyph : public Pokemon {
    Sigilyph() : Pokemon(1, 72, 56, 80, 103, 80, 97) {}

    Sigilyph(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Sigilyph";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SIGILYPH;
    }
};
