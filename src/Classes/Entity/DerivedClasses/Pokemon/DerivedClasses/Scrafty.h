//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Scrafty : public Pokemon {
    Scrafty() : Pokemon(39, 65, 90, 115, 45, 115, 58) {}

    Scrafty(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Scrafty";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::FIGHTING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SCRAFTY;
    }
};
