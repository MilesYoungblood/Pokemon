//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Cofagrigus : public Pokemon {
    Cofagrigus() : Pokemon(34, 58, 50, 145, 95, 105, 30) {}

    Cofagrigus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Cofagrigus";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GHOST : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::COFAGRIGUS;
    }
};
