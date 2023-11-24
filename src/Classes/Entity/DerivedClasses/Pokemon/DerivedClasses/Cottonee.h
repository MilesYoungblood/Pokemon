//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Cottonee : public Pokemon {
    Cottonee() : Pokemon(1, 40, 27, 60, 37, 50, 66) {}

    Cottonee(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Cottonee";
    }

    // TODO FAIRY
    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::COTTONEE;
    }
};
