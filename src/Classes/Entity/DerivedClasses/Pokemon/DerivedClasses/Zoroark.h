//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Zoroark : public Pokemon {
    Zoroark() : Pokemon(30, 60, 105, 60, 120, 60, 105) {}

    Zoroark(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Zoroark";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ZOROARK;
    }
};
