//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Gothorita : public Pokemon {
    Gothorita() : Pokemon(32, 60, 45, 70, 75, 85, 55) {}

    Gothorita(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Gothorita";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 100;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GOTHORITA;
    }
};
