//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Sawsbuck : public Pokemon {
    Sawsbuck() : Pokemon(34, 80, 100, 70, 60, 70, 95) {}

    Sawsbuck(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Sawsbuck";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::GRASS;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SAWSBUCK;
    }
};
