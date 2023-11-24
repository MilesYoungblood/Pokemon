//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Pignite : public Pokemon {
    Pignite() : Pokemon(17, 90, 93, 55, 70, 55, 55) {}

    Pignite(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Pignite";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIRE : Type::FIGHTING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PIGNITE;
    }
};
