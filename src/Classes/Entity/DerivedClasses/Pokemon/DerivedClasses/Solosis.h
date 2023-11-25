//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Solosis : public Pokemon {
    Solosis() : Pokemon(1, 45, 30, 40, 105, 50, 20) {}

    Solosis(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Solosis";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 200;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SOLOSIS;
    }
};
