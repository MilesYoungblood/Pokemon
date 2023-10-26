//
// Created by Miles on 10/5/2023.
//

#pragma once

#include "../../Data/ItemList.h"

namespace ItemFactory {
    inline std::unique_ptr<Item> getItem(const ItemID id, const int quantity) {
        switch (id) {
            case ItemID::POTION:
                return std::make_unique<Potion>(quantity);
            case ItemID::SUPER_POTION:
                return std::make_unique<SuperPotion>(quantity);
            case ItemID::HYPER_POTION:
                return std::make_unique<HyperPotion>(quantity);
            case ItemID::ETHER:
                return std::make_unique<Ether>(quantity);
            case ItemID::ANTIDOTE:
                return std::make_unique<Antidote>(quantity);
            case ItemID::AWAKENING:
                return std::make_unique<Awakening>(quantity);
            case ItemID::BURN_HEAL:
                return std::make_unique<BurnHeal>(quantity);
            case ItemID::ICE_HEAL:
                return std::make_unique<IceHeal>(quantity);
            case ItemID::PARALYZE_HEAL:
                return std::make_unique<ParalyzeHeal>(quantity);
            case ItemID::POKE_BALL:
                return std::make_unique<PokeBall>(quantity);
            case ItemID::GREAT_BALL:
                return std::make_unique<GreatBall>(quantity);
            case ItemID::ULTRA_BALL:
                return std::make_unique<UltraBall>(quantity);
            case ItemID::MASTER_BALL:
                return std::make_unique<MasterBall>(quantity);
            case ItemID::X_ATTACK:
                return std::make_unique<XAttack>(quantity);
            case ItemID::X_DEFENSE:
                return std::make_unique<XDefense>(quantity);
            case ItemID::X_SP_ATTACK:
                return std::make_unique<XSpAttack>(quantity);
            case ItemID::X_SP_DEFENSE:
                return std::make_unique<XSpDefense>(quantity);
            case ItemID::X_SPEED:
                return std::make_unique<XSpeed>(quantity);
            case ItemID::X_ACCURACY:
                return std::make_unique<XAccuracy>(quantity);
            default:
                return nullptr;
        }
    }
}
