//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Herdier : public Pokemon {
    Herdier() : Pokemon(16, 65, 80, 65, 35, 65, 60) {}

    Herdier(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Herdier";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::HERDIER;
    }
};

