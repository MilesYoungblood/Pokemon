//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Gurdurr : public Pokemon {
    Gurdurr() : Pokemon(25, 85, 105, 85, 40, 50, 40) {}

    Gurdurr(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Gurdurr";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIGHTING : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GURDURR;
    }
};
