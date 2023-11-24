//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Crustle : public Pokemon {
    Crustle() : Pokemon(34, 70, 105, 125, 65, 75, 45) {}

    Crustle(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Crustle";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::ROCK;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::CRUSTLE;
    }
};
