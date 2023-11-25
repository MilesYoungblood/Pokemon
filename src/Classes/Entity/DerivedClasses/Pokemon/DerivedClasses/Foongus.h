//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Foongus : public Pokemon {
    Foongus() : Pokemon(1, 69, 55, 45, 55, 55, 15) {}

    Foongus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Foongus";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::POISON;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::FOONGUS;
    }
};
