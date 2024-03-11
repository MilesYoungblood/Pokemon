//
// Created by Miles Youngblood on 12/6/2023.
//

#include "HealBall.h"

HealBall::HealBall(int n) : PokeBall(n) {}

HealBall::HealBall(int n, int x, int y) : PokeBall(n, x, y) {}

std::string HealBall::getName() const {
    return "Heal Ball";
}

std::string HealBall::getEffect() const {
    return "A remedial Poké Ball that restores the caught Pokémon’s HP and eliminates any status problem.";
}

void HealBall::postCatch(Pokemon &pokemon) const {
    pokemon.restoreHp(pokemon.getMaxHp() - pokemon.getHp());
    pokemon.setStatus(StatusCondition::NONE);
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(itemMutex);
        itemMap["Heal Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<HealBall>(n); };
    });
}
