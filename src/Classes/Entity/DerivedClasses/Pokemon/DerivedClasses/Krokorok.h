//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Krokorok : public Pokemon {
    Krokorok() : Pokemon(29, 60, 82, 45, 45, 45, 74) {}

    Krokorok(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Krokorok";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GROUND : Type::DARK;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::KROKOROK;
    }
};
