//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Trubbish : public Pokemon {
    Trubbish() : Pokemon(1, 50, 50, 62, 40, 62, 65) {}

    Trubbish(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Trubbish";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::POISON : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TRUBBISH;
    }
};
