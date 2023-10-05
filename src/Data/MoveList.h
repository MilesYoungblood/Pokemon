//
// Created by Miles Youngblood on 6/7/2022.
//

#pragma once

#include <random>
#include <iostream>

#include "../Classes/Pokemon/Pokemon.h"

#include "./MoveList/AuraSphere.h"
#include "./MoveList/Flamethrower.h"
#include "./MoveList/FlashCannon.h"
#include "./MoveList/FocusBlast.h"
#include "./MoveList/IceBeam.h"
#include "./MoveList/IronTail.h"
#include "./MoveList/Thunder.h"
#include "./MoveList/VoltTackle.h"
#include "./MoveList/WaterShuriken.h"

//TODO add flinching
struct DarkPulse : public Move {
    DarkPulse() : Move("Dark Pulse", 15, 80, 100, Type::DARK, Category::SPECIAL) {}
};

//TODO add flinching
struct Extrasensory : public Move {
    Extrasensory() : Move("Extrasensory", 15, 90, 100, Type::PSYCHIC, Category::SPECIAL) {}
};

//TODO add flinching
struct AirSlash : public Move {
    AirSlash() : Move("Air Slash", 15, 75, 95, Type::FLYING, Category::SPECIAL) {}
};

struct DragonPulse : public Move {
    DragonPulse() : Move("Dragon Pulse", 10, 85, 100, Type::DRAGON, Category::SPECIAL) {}
};

//TODO solar beam
struct SolarBeam : public Move {
    SolarBeam() : Move("Solar Beam", 10, 120, 100, Type::GRASS, Category::SPECIAL) {}
};

//TODO priority
struct QuickAttack : public Move {
    QuickAttack() : Move("Quick Attack", 30, 40, 100, Type::NORMAL, Category::PHYSICAL) {}
};