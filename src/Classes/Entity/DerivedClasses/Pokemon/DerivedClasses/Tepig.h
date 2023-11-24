//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Tepig : public Pokemon {
    Tepig() : Pokemon(1, 65, 63, 45, 45, 45, 45) {}

    Tepig(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Tepig";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIRE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TEPIG;
    }
};
