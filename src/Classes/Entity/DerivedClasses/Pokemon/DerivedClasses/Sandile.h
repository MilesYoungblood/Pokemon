//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Sandile : public Pokemon {
    Sandile() : Pokemon(1, 50, 72, 35, 35, 35, 65) {}

    Sandile(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Sandile";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GROUND : Type::DARK;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 180;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SANDILE;
    }
};
