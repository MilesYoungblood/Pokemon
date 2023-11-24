//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Pidove : public Pokemon {
    Pidove() : Pokemon(1, 50, 55, 50, 36, 30, 43) {}

    Pidove(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Pidove";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PIDOVE;
    }
};
