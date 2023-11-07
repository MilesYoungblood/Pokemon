//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../Classes/Move/MoveList.h"

namespace MoveFactory {
    inline std::unique_ptr<Move> getMove(const Move::ID id, const int pp = -1) {
        switch (id) {
            case Move::ID::AIR_SLASH:
                return std::make_unique<AirSlash>(pp);
            case Move::ID::AURA_SPHERE:
                return std::make_unique<AuraSphere>(pp);
            case Move::ID::DARK_PULSE:
                return std::make_unique<DarkPulse>(pp);
            case Move::ID::DRAGON_PULSE:
                return std::make_unique<DragonPulse>(pp);
            case Move::ID::EXTRASENSORY:
                return std::make_unique<Extrasensory>(pp);
            case Move::ID::FLAMETHROWER:
                return std::make_unique<Flamethrower>(pp);
            case Move::ID::FLASH_CANNON:
                return std::make_unique<FlashCannon>(pp);
            case Move::ID::FOCUS_BLAST:
                return std::make_unique<FocusBlast>(pp);
            case Move::ID::ICE_BEAM:
                return std::make_unique<IceBeam>(pp);
            case Move::ID::IRON_TAIL:
                return std::make_unique<IronTail>(pp);
            case Move::ID::QUICK_ATTACK:
                return std::make_unique<QuickAttack>(pp);
            case Move::ID::SOLAR_BEAM:
                return std::make_unique<SolarBeam>(pp);
            case Move::ID::THUNDER:
                return std::make_unique<Thunder>(pp);
            case Move::ID::VOLT_TACKLE:
                return std::make_unique<VoltTackle>(pp);
            case Move::ID::WATER_SHURIKEN:
                return std::make_unique<WaterShuriken>(pp);
            default:
                return nullptr;
        }
    }
}
