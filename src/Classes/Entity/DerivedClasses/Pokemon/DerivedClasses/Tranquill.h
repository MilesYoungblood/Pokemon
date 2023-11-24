//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Tranquill : public Pokemon {
    Tranquill() : Pokemon(21, 62, 77, 62, 50, 42, 65) {}

    Tranquill(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Tranquill";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TRANQUILL;
    }
};

