//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Frillish : public Pokemon {
    Frillish() : Pokemon(1, 55, 40, 50, 65, 85, 40) {}

    Frillish(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Frillish";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::GHOST;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::FRILLISH;
    }
};
