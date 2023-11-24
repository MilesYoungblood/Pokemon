//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Swoobat : public Pokemon {
    Swoobat() : Pokemon(1, 67, 57, 55, 77, 55, 114) {}

    Swoobat(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Woobat";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SWOOBAT;
    }
};
