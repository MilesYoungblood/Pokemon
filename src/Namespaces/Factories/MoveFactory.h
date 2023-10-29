//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../Classes/Move/MoveList.h"

namespace MoveFactory {
    inline std::unique_ptr<Move> getMove(const MoveID id, const int pp = -1) {
        switch (id) {
            case MoveID::AIR_SLASH:
                return std::make_unique<AirSlash>(pp);
            case MoveID::AURA_SPHERE:
                return std::make_unique<AuraSphere>(pp);
            case MoveID::DARK_PULSE:
                return std::make_unique<DarkPulse>(pp);
            case MoveID::DRAGON_PULSE:
                return std::make_unique<DragonPulse>(pp);
            case MoveID::EXTRASENSORY:
                return std::make_unique<Extrasensory>(pp);
            case MoveID::FLAMETHROWER:
                return std::make_unique<Flamethrower>(pp);
            case MoveID::FLASH_CANNON:
                return std::make_unique<FlashCannon>(pp);
            case MoveID::FOCUS_BLAST:
                return std::make_unique<FocusBlast>(pp);
            case MoveID::ICE_BEAM:
                return std::make_unique<IceBeam>(pp);
            case MoveID::IRON_TAIL:
                return std::make_unique<IronTail>(pp);
            case MoveID::QUICK_ATTACK:
                return std::make_unique<QuickAttack>(pp);
            case MoveID::SOLAR_BEAM:
                return std::make_unique<SolarBeam>(pp);
            case MoveID::THUNDER:
                return std::make_unique<Thunder>(pp);
            case MoveID::VOLT_TACKLE:
                return std::make_unique<VoltTackle>(pp);
            case MoveID::WATER_SHURIKEN:
                return std::make_unique<WaterShuriken>(pp);
            default:
                return nullptr;
        }
    }
}
