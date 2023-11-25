//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Gothita : public Pokemon {
    Gothita() : Pokemon(1, 45, 30, 50, 55, 65, 45) {}

    Gothita(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Gothita";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 200;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GOTHITA;
    }
};
