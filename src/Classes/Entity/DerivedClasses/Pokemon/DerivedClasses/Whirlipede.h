//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Whirlipede : public Pokemon {
    Whirlipede() : Pokemon(22, 40, 55, 99, 40, 79, 47) {}

    Whirlipede(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Whirlipede";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::POISON;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::WHIRLIPEDE;
    }
};
