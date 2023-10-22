//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

#include "../../Entity/DerivedClasses/Pokemon/Pokemon.h"

#include "AirSlash.h"
#include "AuraSphere.h"
#include "DarkPulse.h"
#include "Extrasensory.h"
#include "Flamethrower.h"
#include "FlashCannon.h"
#include "FocusBlast.h"
#include "IceBeam.h"
#include "IronTail.h"
#include "Thunder.h"
#include "VoltTackle.h"
#include "WaterShuriken.h"

struct DragonPulse : public Move {
    DragonPulse() : Move("Dragon Pulse", 10, 85, 100, Type::DRAGON, Category::SPECIAL) {}

    [[nodiscard]] MoveID getID() const override {
        return MoveID::DRAGON_PULSE;
    }
};

//TODO solar beam
struct SolarBeam : public Move {
    SolarBeam() : Move("Solar Beam", 10, 120, 100, Type::GRASS, Category::SPECIAL) {}

    [[nodiscard]] MoveID getID() const override {
        return MoveID::SOLAR_BEAM;
    }
};

//TODO priority
struct QuickAttack : public Move {
    QuickAttack() : Move("Quick Attack", 30, 40, 100, Type::NORMAL, Category::PHYSICAL) {}

    [[nodiscard]] MoveID getID() const override {
        return MoveID::QUICK_ATTACK;
    }
};
