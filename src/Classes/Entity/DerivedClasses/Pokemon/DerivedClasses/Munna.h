//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Munna : public Pokemon {
    Munna() : Pokemon(1, 76, 25, 45, 67, 55, 24) {}

    Munna(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Munna";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::MUNNA;
    }
};
