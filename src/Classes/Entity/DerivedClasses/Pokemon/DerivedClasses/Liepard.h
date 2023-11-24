//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Liepard : public Pokemon {
    Liepard() : Pokemon(20, 64, 88, 50, 88, 50, 106) {}

    Liepard(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Liepard";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::LIEPARD;
    }
};
