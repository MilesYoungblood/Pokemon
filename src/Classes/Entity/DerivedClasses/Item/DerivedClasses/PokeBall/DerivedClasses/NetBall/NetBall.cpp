//
// Created by Miles Youngblood on 12/6/2023.
//

#include "NetBall.h"

NetBall::NetBall(const int n) : PokeBall("Net Ball", n) {}

NetBall::NetBall(const int n, const int x, const int y) : PokeBall("Net Ball", n, x, y) {}

std::string NetBall::getEffect() const {
    return "A somewhat different Poke Ball that works especially well on Water- and Bug-type Pokemon.";
}

double NetBall::getCatchRate(const Pokemon &pokemon, const std::size_t  /*turn*/, const bool  /*isCave*/) const {
    if (pokemon.getType1() == Type::WATER or pokemon.getType1() == Type::BUG or
        pokemon.getType2() == Type::WATER or pokemon.getType2() == Type::BUG) {
        return 3.5;
    }
    return 1.0;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Net Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<NetBall>(n); };
    });
}
