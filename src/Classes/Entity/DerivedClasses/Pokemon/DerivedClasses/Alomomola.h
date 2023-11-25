//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Alomomola : public Pokemon {
    Alomomola() : Pokemon(1, 165, 75, 80, 40, 45, 65) {}

    Alomomola(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Alomomola";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ALOMOMOLA;
    }
};
