//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Ferroseed : public Pokemon {
    Ferroseed() : Pokemon(1, 44, 50, 91, 24, 86, 10) {}

    Ferroseed(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Ferroseed";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::STEEL;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::FERROSEED;
    }
};
