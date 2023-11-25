//
// Created by Miles on 11/24/2023.
//

#pragma once

struct Jellicent : public Pokemon {
    Jellicent() : Pokemon(40, 100, 60, 70, 85, 105, 60) {}

    Jellicent(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Jellicent";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::GHOST;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::JELLICENT;
    }
};
