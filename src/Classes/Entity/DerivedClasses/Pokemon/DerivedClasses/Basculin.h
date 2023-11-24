//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Basculin : public Pokemon {
    Basculin() : Pokemon(1, 70, 92, 65, 80, 55, 98) {}

    Basculin(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Basculin";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 25;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::BASCULIN;
    }
};
