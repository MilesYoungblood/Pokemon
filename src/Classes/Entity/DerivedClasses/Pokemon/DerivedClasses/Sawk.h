//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Sawk : public Pokemon {
    Sawk() : Pokemon(1, 75, 125, 75, 30, 75, 85) {}

    Sawk(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Sawk";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIGHTING : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SAWK;
    }
};
