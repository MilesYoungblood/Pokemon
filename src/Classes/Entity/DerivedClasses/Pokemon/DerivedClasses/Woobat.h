//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Woobat : public Pokemon {
    Woobat() : Pokemon(1, 65, 45, 43, 55, 43, 72) {}

    Woobat(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Woobat";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::WOOBAT;
    }
};
