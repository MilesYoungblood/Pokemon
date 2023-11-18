//
// Created by Miles on 10/5/2023.
//

#pragma once

#include "../../Classes/Item/ItemList.h"

namespace ItemFactory {
    template<typename I, typename ...Args>
    inline I getItem(Args ...args) {
        Item *ptr = std::make_unique<I>(args...);
        return *static_cast<I *>(ptr);
    }

    template<typename I, typename ...Args>
    inline I getItem(Item::Id id, Args ...args) {
        switch (id) {
            case Item::Id::POTION:
                return Potion(args...);
            case Item::Id::SUPER_POTION:
                return SuperPotion(args...);
            case Item::Id::HYPER_POTION:
                return HyperPotion(args...);
            case Item::Id::ETHER:
                return Ether(args...);
            case Item::Id::ANTIDOTE:
                return Antidote(args...);
            case Item::Id::AWAKENING:
                return Awakening(args...);
            case Item::Id::BURN_HEAL:
                return BurnHeal(args...);
            case Item::Id::ICE_HEAL:
                return IceHeal(args...);
            case Item::Id::PARALYZE_HEAL:
                return ParalyzeHeal(args...);
            case Item::Id::POKE_BALL:
                return PokeBall(args...);
            case Item::Id::GREAT_BALL:
                return GreatBall(args...);
            case Item::Id::ULTRA_BALL:
                return UltraBall(args...);
            case Item::Id::MASTER_BALL:
                return MasterBall(args...);
            case Item::Id::NET_BALL:
                return NetBall(args...);
            case Item::Id::NEST_BALL:
                return NetBall(args...);
            case Item::Id::TIMER_BALL:
                // TODO
                break;
            case Item::Id::PREMIER_BALL:
                // TODO
                break;
            case Item::Id::DUSK_BALL:
                // TODO
                break;
            case Item::Id::HEAL_BALL:
                // TODO
                break;
            case Item::Id::QUICK_BALL:
                // TODO
                break;
            case Item::Id::X_ATTACK:
                return XAttack(args...);
            case Item::Id::X_DEFENSE:
                return XDefense(args...);
            case Item::Id::X_SP_ATTACK:
                return XSpAttack(args...);
            case Item::Id::X_SP_DEFENSE:
                return XSpDefense(args...);
            case Item::Id::X_SPEED:
                return XSpeed(args...);
            case Item::Id::X_ACCURACY:
                return XAccuracy(args...);
        }
    }

    template<typename ...Args>
    inline std::unique_ptr<Item> getItem(Item::Id id, Args ...args) {
        switch (id) {
            case Item::Id::POTION:
                return std::make_unique<Potion>(args...);
            case Item::Id::SUPER_POTION:
                return std::make_unique<SuperPotion>(args...);
            case Item::Id::HYPER_POTION:
                return std::make_unique<HyperPotion>(args...);
            case Item::Id::ETHER:
                return std::make_unique<Ether>(args...);
            case Item::Id::ANTIDOTE:
                return std::make_unique<Antidote>(args...);
            case Item::Id::AWAKENING:
                return std::make_unique<Awakening>(args...);
            case Item::Id::BURN_HEAL:
                return std::make_unique<BurnHeal>(args...);
            case Item::Id::ICE_HEAL:
                return std::make_unique<IceHeal>(args...);
            case Item::Id::PARALYZE_HEAL:
                return std::make_unique<ParalyzeHeal>(args...);
            case Item::Id::POKE_BALL:
                return std::make_unique<PokeBall>(args...);
            case Item::Id::GREAT_BALL:
                return std::make_unique<GreatBall>(args...);
            case Item::Id::ULTRA_BALL:
                return std::make_unique<UltraBall>(args...);
            case Item::Id::MASTER_BALL:
                return std::make_unique<MasterBall>(args...);
            case Item::Id::NET_BALL:
                return std::make_unique<NetBall>(args...);
            case Item::Id::X_ATTACK:
                return std::make_unique<XAttack>(args...);
            case Item::Id::X_DEFENSE:
                return std::make_unique<XDefense>(args...);
            case Item::Id::X_SP_ATTACK:
                return std::make_unique<XSpAttack>(args...);
            case Item::Id::X_SP_DEFENSE:
                return std::make_unique<XSpDefense>(args...);
            case Item::Id::X_SPEED:
                return std::make_unique<XSpeed>(args...);
            case Item::Id::X_ACCURACY:
                return std::make_unique<XAccuracy>(args...);
            default:
                return nullptr;
        }
    }
}
