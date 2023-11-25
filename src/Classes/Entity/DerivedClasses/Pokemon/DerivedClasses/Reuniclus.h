//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Reuniclus : public Pokemon {
    Reuniclus() : Pokemon(41, 110, 65, 75, 125, 85, 30) {}

    Reuniclus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Reuniclus";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 50;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::REUNICLUS;
    }
};
