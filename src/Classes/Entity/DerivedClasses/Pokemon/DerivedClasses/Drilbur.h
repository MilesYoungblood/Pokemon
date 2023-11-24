//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Drilbur : public Pokemon {
    Drilbur() : Pokemon(1, 60, 85, 40, 30, 45, 68) {}

    Drilbur(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Drilbur";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GROUND : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DRILBUR;
    }
};
