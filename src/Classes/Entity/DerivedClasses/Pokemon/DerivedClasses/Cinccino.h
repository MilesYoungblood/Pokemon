//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Cinccino : public Pokemon {
    Cinccino() : Pokemon(1, 75, 95, 60, 65, 60, 115) {}

    Cinccino(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Cinccino";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::CINCCINO;
    }
};
