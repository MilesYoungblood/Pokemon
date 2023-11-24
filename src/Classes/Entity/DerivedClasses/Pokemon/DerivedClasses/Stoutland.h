//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Stoutland : public Pokemon {
    Stoutland() : Pokemon(32, 85, 110, 90, 45, 90, 80) {}

    Stoutland(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Stoutland";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::STOUTLAND;
    }
};
