//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../Classes/Move/MoveList.h"

namespace MoveFactory {
    inline std::unique_ptr<Move> getMove(Move::Id id, const int pp = -1) {
        switch (id) {
            case Move::Id::AIR_SLASH:
                return std::make_unique<AirSlash>(pp);
            case Move::Id::AURA_SPHERE:
                return std::make_unique<AuraSphere>(pp);
            case Move::Id::DARK_PULSE:
                return std::make_unique<DarkPulse>(pp);
            case Move::Id::DRAGON_PULSE:
                return std::make_unique<DragonPulse>(pp);
            case Move::Id::EXTRASENSORY:
                return std::make_unique<Extrasensory>(pp);
            case Move::Id::FLAMETHROWER:
                return std::make_unique<Flamethrower>(pp);
            case Move::Id::FLASH_CANNON:
                return std::make_unique<FlashCannon>(pp);
            case Move::Id::FOCUS_BLAST:
                return std::make_unique<FocusBlast>(pp);
            case Move::Id::ICE_BEAM:
                return std::make_unique<IceBeam>(pp);
            case Move::Id::IRON_TAIL:
                return std::make_unique<IronTail>(pp);
            case Move::Id::QUICK_ATTACK:
                return std::make_unique<QuickAttack>(pp);
            case Move::Id::SOLAR_BEAM:
                return std::make_unique<SolarBeam>(pp);
            case Move::Id::THUNDER:
                return std::make_unique<Thunder>(pp);
            case Move::Id::VOLT_TACKLE:
                return std::make_unique<VoltTackle>(pp);
            case Move::Id::WATER_SHURIKEN:
                return std::make_unique<WaterShuriken>(pp);
            default:
                return nullptr;
        }
    }
}
