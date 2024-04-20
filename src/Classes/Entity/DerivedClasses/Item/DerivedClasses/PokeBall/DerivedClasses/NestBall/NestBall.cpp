//
// Created by Miles Youngblood on 12/6/2023.
//

#include "NestBall.h"

NestBall::NestBall(const int n) : PokeBall("Nest Ball", n) {}

NestBall::NestBall(const int n, const int x, const int y) : PokeBall("Nest Ball", n, x, y) {}

std::string NestBall::getEffect() const {
    return "A somewhat different Poke Ball that works especially well on weaker Pokemon in the wild.";
}

double NestBall::getCatchRate(const Pokemon &pokemon, const std::size_t  /*turn*/, const bool  /*isCave*/) const {
    return (41 - pokemon.getLevel()) * 4069 / 10.0 / 4096.0;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Nest Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<NestBall>(n); };
    });
}
