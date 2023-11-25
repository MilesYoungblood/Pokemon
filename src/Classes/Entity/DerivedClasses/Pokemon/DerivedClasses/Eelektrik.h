//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Eelektrik : public Pokemon {
    Eelektrik() : Pokemon(39, 65, 85, 70, 75, 70, 40) {}

    Eelektrik(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Eelektrik";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::EELEKTRIK;
    }
};
