//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Galvantula : public Pokemon {
    Galvantula() : Pokemon(36, 70, 77, 60, 97, 60, 108) {}

    Galvantula(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Galvantula";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::ELECTRIC;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GALVANTULA;
    }
};
