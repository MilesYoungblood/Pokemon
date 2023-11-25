//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Gothitelle : public Pokemon {
    Gothitelle() : Pokemon(41, 70, 55, 95, 95, 110, 65) {}

    Gothitelle(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Gothitelle";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 50;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GOTHITELLE;
    }
};
