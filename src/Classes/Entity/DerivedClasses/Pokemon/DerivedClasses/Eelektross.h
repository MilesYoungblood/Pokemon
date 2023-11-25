//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Eelektross : public Pokemon {
    Eelektross() : Pokemon(39, 85, 115, 80, 105, 80, 50) {}

    Eelektross(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Eelektross";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 30;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::EELEKTROSS;
    }
};
