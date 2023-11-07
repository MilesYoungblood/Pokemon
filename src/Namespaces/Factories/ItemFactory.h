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

    inline std::unique_ptr<Item> getItem(const Item::ID id, const int quantity) {
        switch (id) {
            case Item::ID::POTION:
                return std::make_unique<Potion>(quantity);
            case Item::ID::SUPER_POTION:
                return std::make_unique<SuperPotion>(quantity);
            case Item::ID::HYPER_POTION:
                return std::make_unique<HyperPotion>(quantity);
            case Item::ID::ETHER:
                return std::make_unique<Ether>(quantity);
            case Item::ID::ANTIDOTE:
                return std::make_unique<Antidote>(quantity);
            case Item::ID::AWAKENING:
                return std::make_unique<Awakening>(quantity);
            case Item::ID::BURN_HEAL:
                return std::make_unique<BurnHeal>(quantity);
            case Item::ID::ICE_HEAL:
                return std::make_unique<IceHeal>(quantity);
            case Item::ID::PARALYZE_HEAL:
                return std::make_unique<ParalyzeHeal>(quantity);
            case Item::ID::POKE_BALL:
                return std::make_unique<PokeBall>(quantity);
            case Item::ID::GREAT_BALL:
                return std::make_unique<GreatBall>(quantity);
            case Item::ID::ULTRA_BALL:
                return std::make_unique<UltraBall>(quantity);
            case Item::ID::MASTER_BALL:
                return std::make_unique<MasterBall>(quantity);
            case Item::ID::NET_BALL:
                return std::make_unique<NetBall>(quantity);
            case Item::ID::X_ATTACK:
                return std::make_unique<XAttack>(quantity);
            case Item::ID::X_DEFENSE:
                return std::make_unique<XDefense>(quantity);
            case Item::ID::X_SP_ATTACK:
                return std::make_unique<XSpAttack>(quantity);
            case Item::ID::X_SP_DEFENSE:
                return std::make_unique<XSpDefense>(quantity);
            case Item::ID::X_SPEED:
                return std::make_unique<XSpeed>(quantity);
            case Item::ID::X_ACCURACY:
                return std::make_unique<XAccuracy>(quantity);
            default:
                return nullptr;
        }
    }
}
