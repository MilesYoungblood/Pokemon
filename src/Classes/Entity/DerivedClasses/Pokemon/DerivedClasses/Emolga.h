//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Emolga : public Pokemon {
    Emolga() : Pokemon(1, 55, 75, 60, 75, 60, 103) {}

    Emolga(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Emolga";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 200;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::EMOLGA;
    }
};
