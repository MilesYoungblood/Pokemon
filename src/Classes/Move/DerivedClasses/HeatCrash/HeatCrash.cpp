//
// Created by Miles Youngblood on 3/4/2024.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "HeatCrash.h"

HeatCrash::HeatCrash() : Move(10) {}

int HeatCrash::getDamage(const Pokemon &attacker, const Pokemon &defender) const {
    double ratio = attacker.getWeight() / defender.getWeight();
    int power;
    if (5 <= ratio) {
        power = 120;
    }
    else if (4 <= ratio and ratio < 5) {
        power = 100;
    }
    else if (3 <= ratio and ratio < 4) {
        power = 80;
    }
    else if (2 <= ratio and ratio < 3) {
        power = 60;
    }
    else {
        power = 40;
    }
    return binomial(static_cast<double>(this->getAccuracy())) ? power : -1;
}

std::string HeatCrash::getName() const {
    return "Heat Crash";
}

const char *HeatCrash::getDescription() const {
    return "The user slams its target with its flame-covered body. The more the user outweighs the target, the greater the damage.";
}

int HeatCrash::getPower() const {
    return 1;
}

Type HeatCrash::getType() const {
    return Type::FIRE;
}

Move::Category HeatCrash::getCategory() const {
    return Move::Category::PHYSICAL;
}

Move::Id HeatCrash::getId() const {
    return Move::Id::HEAT_CRASH;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(moveMutex);
        moveMap.insert(std::make_pair(Move::Id::HEAT_CRASH,
                                      [] -> std::unique_ptr<Move> { return std::make_unique<HeatCrash>(); }));
    });
}
