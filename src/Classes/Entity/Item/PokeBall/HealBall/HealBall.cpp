//
// Created by Miles Youngblood on 12/6/2023.
//

#include "HealBall.h"

HealBall::HealBall(const int n) : PokeBall("Heal Ball", n) {}

HealBall::HealBall(const int n, const int x, const int y) : PokeBall("Heal Ball", n, x, y) {}

std::string HealBall::getEffect() const {
    return "A remedial Poké Ball that restores the caught Pokémon’s HP and eliminates any status problem.";
}

void HealBall::postCatch(Pokemon &pokemon) const {
    pokemon.getHp().fill();
    pokemon.setStatus(StatusCondition::NONE);
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Heal Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<HealBall>(n); };
    });
}
