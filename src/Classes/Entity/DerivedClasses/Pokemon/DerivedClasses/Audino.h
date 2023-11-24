//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Audino : public Pokemon {
    Audino() : Pokemon(1, 103, 60, 86, 60, 86, 50) {}

    Audino(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Audino";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::AUDINO;
    }
};
