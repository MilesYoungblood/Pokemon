//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../Data/MoveList.h"

namespace MoveFactory {
    inline Move *getMove(MoveID id) {
        switch (id) {
            case MoveID::AIR_SLASH:
                return new AirSlash();
            case MoveID::AURA_SPHERE:
                return new AuraSphere();
            case MoveID::DARK_PULSE:
                return new DarkPulse();
            case MoveID::DRAGON_PULSE:
                return new DragonPulse();
            case MoveID::EXTRASENSORY:
                return new Extrasensory();
            case MoveID::FLAMETHROWER:
                return new Flamethrower();
            case MoveID::FLASH_CANNON:
                return new FlashCannon();
            case MoveID::FOCUS_BLAST:
                return new FocusBlast();
            case MoveID::ICE_BEAM:
                return new IceBeam();
            case MoveID::IRON_TAIL:
                return new IronTail();
            case MoveID::QUICK_ATTACK:
                return new QuickAttack();
            case MoveID::SOLAR_BEAM:
                return new SolarBeam();
            case MoveID::THUNDER:
                return new Thunder();
            case MoveID::VOLT_TACKLE:
                return new VoltTackle();
            case MoveID::WATER_SHURIKEN:
                return new WaterShuriken();
            default:
                return nullptr;
        }
    }

}