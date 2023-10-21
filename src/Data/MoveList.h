//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

#include <random>
#include <iostream>

#include "../Classes/Pokemon/Pokemon.h"

#include "./MoveList/AirSlash.h"
#include "./MoveList/AuraSphere.h"
#include "./MoveList/DarkPulse.h"
#include "./MoveList/Extrasensory.h"
#include "./MoveList/Flamethrower.h"
#include "./MoveList/FlashCannon.h"
#include "./MoveList/FocusBlast.h"
#include "./MoveList/IceBeam.h"
#include "./MoveList/IronTail.h"
#include "./MoveList/Thunder.h"
#include "./MoveList/VoltTackle.h"
#include "./MoveList/WaterShuriken.h"

struct DragonPulse : public Move {
    DragonPulse() : Move("Dragon Pulse", 10, 85, 100, Type::DRAGON, Category::SPECIAL) {}

    auto getID() -> MoveID override {
        return MoveID::DRAGON_PULSE;
    }
};

//TODO solar beam
struct SolarBeam : public Move {
    SolarBeam() : Move("Solar Beam", 10, 120, 100, Type::GRASS, Category::SPECIAL) {}

    auto getID() -> MoveID override {
        return MoveID::SOLAR_BEAM;
    }
};

//TODO priority
struct QuickAttack : public Move {
    QuickAttack() : Move("Quick Attack", 30, 40, 100, Type::NORMAL, Category::PHYSICAL) {}

    auto getID() -> MoveID override {
        return MoveID::QUICK_ATTACK;
    }
};
