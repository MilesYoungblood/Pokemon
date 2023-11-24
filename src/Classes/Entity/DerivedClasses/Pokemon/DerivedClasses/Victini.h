//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Victini : public Pokemon {
    Victini() : Pokemon(15, 100, 100, 100, 100, 100, 100) {}

    Victini(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Victini";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::FIRE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::VICTINI;
    }
};
