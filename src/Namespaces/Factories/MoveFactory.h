//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../Classes/Move/MoveList.h"

namespace MoveFactory {
    template<typename ...Args>
    inline std::unique_ptr<Move> getMove(Move::Id id, Args ...args) {
        switch (id) {
            case Move::Id::AIR_SLASH:
                return std::make_unique<AirSlash>(args...);
            case Move::Id::AURA_SPHERE:
                return std::make_unique<AuraSphere>(args...);
            case Move::Id::DARK_PULSE:
                return std::make_unique<DarkPulse>(args...);
            case Move::Id::DRAGON_PULSE:
                return std::make_unique<DragonPulse>(args...);
            case Move::Id::EXTRASENSORY:
                return std::make_unique<Extrasensory>(args...);
            case Move::Id::FLAMETHROWER:
                return std::make_unique<Flamethrower>(args...);
            case Move::Id::FLASH_CANNON:
                return std::make_unique<FlashCannon>(args...);
            case Move::Id::FOCUS_BLAST:
                return std::make_unique<FocusBlast>(args...);
            case Move::Id::ICE_BEAM:
                return std::make_unique<IceBeam>(args...);
            case Move::Id::IRON_TAIL:
                return std::make_unique<IronTail>(args...);
            case Move::Id::QUICK_ATTACK:
                return std::make_unique<QuickAttack>(args...);
            case Move::Id::SOLAR_BEAM:
                return std::make_unique<SolarBeam>(args...);
            case Move::Id::THUNDER:
                return std::make_unique<Thunder>(args...);
            case Move::Id::VOLT_TACKLE:
                return std::make_unique<VoltTackle>(args...);
            case Move::Id::WATER_SHURIKEN:
                return std::make_unique<WaterShuriken>(args...);
            default:
                return nullptr;
        }
    }
}
