//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Vanillite : public Pokemon {
    Vanillite() : Pokemon(1, 36, 50, 50, 65, 60, 44) {}

    Vanillite(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Vanillite";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ICE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::VANILLITE;
    }
};
