//
// Created by Miles Youngblood on 12/6/2023.
//

#include "MasterBall.h"

MasterBall::MasterBall(const int n) : PokeBall("Master Ball", n) {}

MasterBall::MasterBall(const int n, const int x, const int y) : PokeBall("Master Ball", n, x, y) {}

std::string MasterBall::getEffect() const {
    return "The best Ball with the ultimate level of performance. It will catch any wild Pokemon without fail.";
}

double MasterBall::getCatchRate(const Pokemon & /*pokemon*/, const std::size_t  /*turn*/, const bool  /*isCave*/) const {
    return 255.0;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Master Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<MasterBall>(n); };
    });
}
