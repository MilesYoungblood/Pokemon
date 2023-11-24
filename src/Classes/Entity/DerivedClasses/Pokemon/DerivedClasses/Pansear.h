//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Pansear : public Pokemon {
    Pansear() : Pokemon(1, 50, 53, 48, 53, 48, 64) {}

    Pansear(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Pansear";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIRE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PANSEAR;
    }
};
