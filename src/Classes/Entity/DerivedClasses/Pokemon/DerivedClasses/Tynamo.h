//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Tynamo : public Pokemon {
    Tynamo() : Pokemon(1, 35, 55, 40, 45, 40, 60) {}

    Tynamo(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Tynamo";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TYNAMO;
    }
};
