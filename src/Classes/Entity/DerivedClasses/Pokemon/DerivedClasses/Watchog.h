//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Watchog : public Pokemon {
    Watchog() : Pokemon(20, 60, 85, 69, 60, 69, 77) {}

    Watchog(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Watchog";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::WATCHOG;
    }
};
