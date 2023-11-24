//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Musharna : public Pokemon {
    Musharna() : Pokemon(1, 116, 55, 85, 107, 95, 29) {}

    Musharna(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Musharna";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::MUSHARNA;
    }
};
