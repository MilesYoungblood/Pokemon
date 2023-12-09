//
// Created by Miles Youngblood on 12/6/2023.
//

#include "NestBall.h"

NestBall::NestBall(int quantity) : PokeBall(quantity) {}

std::string NestBall::getName() const {
    return "Nest Ball";
}

std::string NestBall::getEffect() const {
    return "A somewhat different Poke Ball that works especially well on weaker Pokemon in the wild.";
}

double NestBall::getCatchRate(const Pokemon &pokemon, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const {
    return ((41 - pokemon.getLevel()) * 4069 / 10.0) / 4096.0;
}

PokeBall::Id NestBall::getId() const {
    return PokeBall::Id::NEST_BALL;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokeBallMutex);
        pokeBalls.insert(std::make_pair(PokeBall::Id::NEST_BALL, [](int n) -> std::unique_ptr<PokeBall> {
            return std::make_unique<NestBall>(n);
        }));
    });
}
