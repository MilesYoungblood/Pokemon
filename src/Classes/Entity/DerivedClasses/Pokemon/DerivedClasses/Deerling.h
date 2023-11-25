//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Deerling : public Pokemon {
    Deerling() : Pokemon(1, 60, 60, 50, 40, 50, 75) {}

    Deerling(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Deerling";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::GRASS;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DEERLING;
    }
};
