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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::GREAT_BALL;
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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::ULTRA_BALL;
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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::MASTER_BALL;
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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::NET_BALL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Net Ball";
    }
};

struct NestBall : public PokeBall {
    explicit NestBall(int n) : PokeBall(n) {}

    [[nodiscard]] double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const override {
        return ((41 - pokemon.getLevel()) * 4069 / 10.0) / 4096.0;
    }

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::NEST_BALL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Nest Ball";
    }
};

struct TimerBall : public PokeBall {
    explicit TimerBall(int n) : PokeBall(n) {}

    [[nodiscard]] double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const override {
        return std::min(1 + turn * 1229 / 4069.0, 4.0);
    }

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::TIMER_BALL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Timer Ball";
    }
};

struct PremierBall : public PokeBall {
    explicit PremierBall(int n) : PokeBall(n) {}

    [[nodiscard]] double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const override {
        return 1.0;
    }

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::PREMIER_BALL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Premier Ball";
    }
};

struct DuskBall : public PokeBall {
    explicit DuskBall(int n) : PokeBall(n) {}

    [[nodiscard]] double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const override {
        return time == Time::NIGHT or isCave ? 3.5 : 1.0;
    }

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::DUSK_BALL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Dusk Ball";
    }
};

struct HealBall : public PokeBall {
    explicit HealBall(int n) : PokeBall(n) {}

    [[nodiscard]] double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const override {
        return 1.0;
    }

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::HEAL_BALL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Heal Ball";
    }
};

struct QuickBall : public PokeBall {
    explicit QuickBall(int n) : PokeBall(n) {}

    [[nodiscard]] double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const override {
        return turn > 1ULL ? 1.0 : 5.0;
    }

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::QUICK_BALL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Quick Ball";
    }
};
