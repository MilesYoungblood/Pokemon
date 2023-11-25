//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Swanna : public Pokemon {
    Swanna() : Pokemon(35, 75, 87, 63, 87, 63, 98) {}

    Swanna(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Swanna";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SWANNA;
    }
};
