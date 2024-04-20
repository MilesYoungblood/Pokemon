//
// Created by Miles Youngblood on 3/4/2024.
//

#include "../../Entity/Character/Pokemon/Pokemon.h"
#include "HeatCrash.h"

HeatCrash::HeatCrash() : Move(10) {}

std::string HeatCrash::getName() const {
    return "Heat Crash";
}

std::string HeatCrash::getDescription() const {
    return "The user slams its target with its flame-covered body. The more the user outweighs the target, the greater the damage.";
}

int HeatCrash::getPower(const Pokemon &attacker, const Pokemon &defender) const {
    const double ratio = attacker.getWeight() / defender.getWeight();
    if (5 <= ratio) {
        return 120;
    }
    if (4 <= ratio and ratio < 5) {
        return 100;
    }
    if (3 <= ratio and ratio < 4) {
        return 80;
    }
    if (2 <= ratio and ratio < 3) {
        return 60;
    }
    return 40;
}

Type HeatCrash::getType() const {
    return Type::FIRE;
}

Move::Category HeatCrash::getCategory() const {
    return Category::PHYSICAL;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(moveMutex);
        moveMap["Heat Crash"] = [] -> std::unique_ptr<Move> { return std::make_unique<HeatCrash>(); };
    });
}
