//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Ferrothorn : public Pokemon {
    Ferrothorn() : Pokemon(40, 74, 94, 131, 54, 116, 20) {}

    Ferrothorn(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Ferrothorn";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::STEEL;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::FERROTHORN;
    }
};
