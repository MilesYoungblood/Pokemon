//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../Pokeball.h"

struct GreatBall : public PokeBall {
    explicit GreatBall(int n) : PokeBall(n) {}

    [[nodiscard]] double getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const override {
        return 1.5;
    }

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::GREAT_BALL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Great Ball";
    }
};

struct UltraBall : public PokeBall {
    explicit UltraBall(int n) : PokeBall(n) {}

    [[nodiscard]] double getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const override {
        return 2.0;
    }

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::ULTRA_BALL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Ultra Ball";
    }
};

struct MasterBall : public PokeBall {
    explicit MasterBall(int n) : PokeBall(n) {}

    [[nodiscard]] double getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const override {
        return 255.0;
    }

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::MASTER_BALL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Master Ball";
    }
};

struct NetBall : public PokeBall {
    explicit NetBall(int n) : PokeBall(n) {}

    [[nodiscard]] double getCatchRate(const Pokemon &pokemon, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const override {
        if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::BUG or
            pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::BUG) {
            return 3.5;
        }
        return 1.0;
    }

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::NET_BALL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Net Ball";
    }
};