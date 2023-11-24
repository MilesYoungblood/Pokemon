//
// Created by Miles on 11/23/2023.
//

#pragma once

struct Excadrill : public Pokemon {
    Excadrill() : Pokemon(31, 110, 135, 60, 50, 65, 88) {}

    Excadrill(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Excadrill";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GROUND : Type::STEEL;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::EXCADRILL;
    }
};
