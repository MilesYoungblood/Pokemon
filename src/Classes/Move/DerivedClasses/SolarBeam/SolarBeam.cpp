//
// Created by Miles Youngblood on 12/4/2023.
//

#include "SolarBeam.h"

SolarBeam::SolarBeam() : Move(10) {}

std::string SolarBeam::getName() const {
    return "Solar Beam";
}

const char *SolarBeam::getDescription() const {
    return "A two-turn attack. The user gathers light, then blasts a bundled beam on the second turn.";
}

int SolarBeam::getPower() const {
    return 120;
}

Type SolarBeam::getType() const {
    return Type::GRASS;
}

Move::Category SolarBeam::getCategory() const {
    return Move::Category::SPECIAL;
}

Move::Id SolarBeam::getId() const {
    return Move::Id::SOLAR_BEAM;
}
