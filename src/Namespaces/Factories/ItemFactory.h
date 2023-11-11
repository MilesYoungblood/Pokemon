//
// Created by Miles on 10/5/2023.
//

#pragma once

#include "../../Classes/Item/ItemList.h"

namespace ItemFactory {
    template<typename I>
    inline I *getItem(const int quantity) {
        const std::shared_ptr<I> item = std::make_shared<I>(quantity);
        return item.get();
    }

    inline std::unique_ptr<Item> getItem(const Item::Id id, const int quantity) {
        switch (id) {
            case Item::Id::POTION:
                return std::make_unique<Potion>(quantity);
            case Item::Id::SUPER_POTION:
                return std::make_unique<SuperPotion>(quantity);
            case Item::Id::HYPER_POTION:
                return std::make_unique<HyperPotion>(quantity);
            case Item::Id::ETHER:
                return std::make_unique<Ether>(quantity);
            case Item::Id::ANTIDOTE:
                return std::make_unique<Antidote>(quantity);
            case Item::Id::AWAKENING:
                return std::make_unique<Awakening>(quantity);
            case Item::Id::BURN_HEAL:
                return std::make_unique<BurnHeal>(quantity);
            case Item::Id::ICE_HEAL:
                return std::make_unique<IceHeal>(quantity);
            case Item::Id::PARALYZE_HEAL:
                return std::make_unique<ParalyzeHeal>(quantity);
            case Item::Id::POKE_BALL:
                return std::make_unique<PokeBall>(quantity);
            case Item::Id::GREAT_BALL:
                return std::make_unique<GreatBall>(quantity);
            case Item::Id::ULTRA_BALL:
                return std::make_unique<UltraBall>(quantity);
            case Item::Id::MASTER_BALL:
                return std::make_unique<MasterBall>(quantity);
            case Item::Id::NET_BALL:
                return std::make_unique<NetBall>(quantity);
            case Item::Id::X_ATTACK:
                return std::make_unique<XAttack>(quantity);
            case Item::Id::X_DEFENSE:
                return std::make_unique<XDefense>(quantity);
            case Item::Id::X_SP_ATTACK:
                return std::make_unique<XSpAttack>(quantity);
            case Item::Id::X_SP_DEFENSE:
                return std::make_unique<XSpDefense>(quantity);
            case Item::Id::X_SPEED:
                return std::make_unique<XSpeed>(quantity);
            case Item::Id::X_ACCURACY:
                return std::make_unique<XAccuracy>(quantity);
            default:
                return nullptr;
        }
    }
}
