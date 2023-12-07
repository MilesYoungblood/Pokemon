//
// Created by Miles Youngblood on 12/6/2023.
//

#include "NetBall.h"

NetBall::NetBall(int quantity) : PokeBall(quantity) {}

std::string NetBall::getName() const {
    return "Net Ball";
}

std::string NetBall::getEffect() const {
    return "A somewhat different Poke Ball that works especially well on Water- and Bug-type Pokemon.";
}

double NetBall::getCatchRate(const Pokemon &pokemon, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const {
    if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::BUG or
        pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::BUG) {
        return 3.5;
    }
    return 1.0;
}

PokeBall::Id NetBall::getId() const {
    return PokeBall::Id::NET_BALL;
}

namespace {
    AutoThread init([] -> void {
        pokeBalls.insert(std::make_pair(PokeBall::Id::NET_BALL, [](int n) -> std::unique_ptr<PokeBall> {
            return std::make_unique<NetBall>(n);
        }));
    });
}
