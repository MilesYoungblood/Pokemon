//
// Created by Miles Youngblood on 12/6/2023.
//

#include "DuskBall.h"

DuskBall::DuskBall(int quantity) : PokeBall(quantity) {}

std::string DuskBall::getName() const {
    return "Dusk Ball";
}

std::string DuskBall::getEffect() const {
    return "A somewhat different Poke Ball that makes it easier to catch wild Pokemon at night or in dark places like caves.";
}

double DuskBall::getCatchRate(const Pokemon & /*pokemon*/, Time time, int  /*turn*/, bool isCave) const {
    return time == Time::NIGHT or isCave ? 3.5 : 1.0;
}

PokeBall::Id DuskBall::getId() const {
    return PokeBall::Id::DUSK_BALL;
}

namespace {
    AutoThread init([] -> void {
        pokeBalls.insert(std::make_pair(PokeBall::Id::DUSK_BALL, [](int n) -> std::unique_ptr<PokeBall> {
            return std::make_unique<DuskBall>(n);
        }));
    });
}
