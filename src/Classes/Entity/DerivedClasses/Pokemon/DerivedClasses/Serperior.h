//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Serperior : public Pokemon {
    Serperior() : Pokemon(36, 75, 75, 95, 75, 95, 113) {}

    Serperior(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Serperior";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SERPERIOR;
    }
};
