//
// Created by Miles Youngblood on 12/6/2023.
//

#include "HealBall.h"

HealBall::HealBall(int quantity) : PokeBall(quantity) {}

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

PokeBall::Id HealBall::getId() const {
    return PokeBall::Id::HEAL_BALL;
}

namespace {
    AutoThread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokeBallMutex);
        pokeBalls.insert(std::make_pair(PokeBall::Id::HEAL_BALL, [](int n) -> std::unique_ptr<PokeBall> {
            return std::make_unique<HealBall>(n);
        }));
    });
}
