//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Scolipede : public Pokemon {
    Scolipede() : Pokemon(30, 60, 100, 89, 55, 69, 112) {}

    Scolipede(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Scolipede";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::POISON;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SCOLIPEDE;
    }
};
