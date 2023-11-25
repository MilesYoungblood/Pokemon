//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Garbodor : public Pokemon {
    Garbodor() : Pokemon(36, 80, 95, 82, 60, 82, 75) {}

    Garbodor(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Garbodor";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::POISON : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GARBODOR;
    }
};
