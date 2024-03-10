//
// Created by Miles Youngblood on 12/4/2023.
//

#include "SolarBeam.h"

SolarBeam::SolarBeam() : Move(10) {}

std::string SolarBeam::getName() const {
    return "Solar Beam";
}

std::string SolarBeam::getDescription() const {
    return "A two-turn attack. The user gathers light, then blasts a bundled beam on the second turn.";
}

int SolarBeam::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
    return 120;
}

Type SolarBeam::getType() const {
    return Type::GRASS;
}

Move::Category SolarBeam::getCategory() const {
    return Move::Category::SPECIAL;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(moveMutex);
        moveMap["Solar Beam"] = [] -> std::unique_ptr<Move> { return std::make_unique<SolarBeam>(); };
    });
}
