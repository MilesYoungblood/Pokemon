//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Seismitoad : public Pokemon {
    Seismitoad() : Pokemon(36, 105, 95, 75, 85, 75, 74) {}

    Seismitoad(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Seismitoad";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::GROUND;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SEISMITOAD;
    }
};
