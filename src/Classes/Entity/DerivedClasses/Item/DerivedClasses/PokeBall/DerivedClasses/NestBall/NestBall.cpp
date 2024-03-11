//
// Created by Miles Youngblood on 12/6/2023.
//

#include "NestBall.h"

NestBall::NestBall(int n) : PokeBall(n) {}

NestBall::NestBall(int n, int x, int y) : PokeBall(n, x, y) {}

std::string NestBall::getName() const {
    return "Nest Ball";
}

std::string NestBall::getEffect() const {
    return "A somewhat different Poke Ball that works especially well on weaker Pokemon in the wild.";
}

double NestBall::getCatchRate(const Pokemon &pokemon, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const {
    return ((41 - pokemon.getLevel()) * 4069 / 10.0) / 4096.0;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(itemMutex);
        itemMap["Nest Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<NestBall>(n); };
    });
}
