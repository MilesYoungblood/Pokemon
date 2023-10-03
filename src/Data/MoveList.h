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
    DarkPulse() : Move("Dark Pulse", Type::DARK, Category::SPECIAL, 15, 80, 100) {}
};

//TODO add flinching
struct Extrasensory : public Move {
    Extrasensory() : Move("Extrasensory", Type::PSYCHIC, Category::SPECIAL, 15, 90, 100) {}
};

//TODO add flinching
struct AirSlash : public Move {
    AirSlash() : Move("Air Slash", Type::FLYING, Category::SPECIAL, 15, 75, 95) {}
};

struct DragonPulse : public Move {
    DragonPulse() : Move("Dragon Pulse", Type::DRAGON, Category::SPECIAL, 10, 85, 100) {}
};

//TODO solar beam
struct SolarBeam : public Move {
    SolarBeam() : Move("Solar Beam", Type::GRASS, Category::SPECIAL, 10, 120, 100) {}
};

//TODO priority
struct QuickAttack : public Move {
    QuickAttack() : Move("Quick Attack", Type::NORMAL, Category::PHYSICAL, 30, 40, 100) {}
};