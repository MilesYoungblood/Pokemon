//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Oshawott : public Pokemon {
    Oshawott() : Pokemon(1, 55, 55, 45, 63, 45, 45) {}

    Oshawott(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Oshawott";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::OSHAWOTT;
    }
};
