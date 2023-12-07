//
// Created by Miles Youngblood on 12/6/2023.
//

#include "MasterBall.h"

MasterBall::MasterBall(int quantity) : PokeBall(quantity) {}

std::string MasterBall::getName() const {
    return "Master Ball";
}

std::string MasterBall::getEffect() const {
    return "The best Ball with the ultimate level of performance. It will catch any wild Pokemon without fail.";
}

double MasterBall::getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const {
    return 255.0;
}

PokeBall::Id MasterBall::getId() const {
    return PokeBall::Id::MASTER_BALL;
}

namespace {
    AutoThread init([] -> void {
        pokeBalls.insert(std::make_pair(PokeBall::Id::MASTER_BALL, [](int n) -> std::unique_ptr<PokeBall> {
            return std::make_unique<MasterBall>(n);
        }));
    });
}
