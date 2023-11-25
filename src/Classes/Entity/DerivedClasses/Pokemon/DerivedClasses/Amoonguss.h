//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Amoonguss : public Pokemon {
    Amoonguss() : Pokemon(39, 114, 85, 70, 85, 80, 30) {}

    Amoonguss(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Amoonguss";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::POISON;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::AMOONGUSS;
    }
};
