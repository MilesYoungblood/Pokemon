//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Krookodile : public Pokemon {
    Krookodile() : Pokemon(40, 95, 117, 80, 65, 70, 92) {}

    Krookodile(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Krookodile";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GROUND : Type::DARK;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::KROOKODILE;
    }
};
