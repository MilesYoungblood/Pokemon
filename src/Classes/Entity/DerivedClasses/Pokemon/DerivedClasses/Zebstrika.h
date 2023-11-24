//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Zebstrika : public Pokemon {
    Zebstrika() : Pokemon(27, 75, 100, 63, 80, 63, 116) {}

    Zebstrika(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Zebstrika";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ZEBSTRIKA;
    }
};
