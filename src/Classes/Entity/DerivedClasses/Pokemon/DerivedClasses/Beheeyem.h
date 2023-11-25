//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Beheeyem : public Pokemon {
    Beheeyem() : Pokemon(42, 75, 75, 75, 125, 95, 40) {}

    Beheeyem(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Beheeyem";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::BEHEEYEM;
    }
};
