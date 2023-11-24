//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Scraggy : public Pokemon {
    Scraggy() : Pokemon(1, 50, 75, 70, 35, 70, 48) {}

    Scraggy(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Scraggy";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::FIGHTING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 180;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SCRAGGY;
    }
};
