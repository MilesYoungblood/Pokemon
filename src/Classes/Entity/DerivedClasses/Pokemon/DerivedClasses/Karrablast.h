//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Karrablast : public Pokemon {
    Karrablast() : Pokemon(1, 50, 75, 45, 40, 45, 60) {}

    Karrablast(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Karrablast";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 200;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::KARRABLAST;
    }
};
