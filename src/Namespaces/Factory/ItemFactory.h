//
// Created by Miles on 10/5/2023.
//

#pragma once

#include "../../Data/ItemList.h"

namespace ItemFactory {
    inline Item * getItem(const ItemID id, const int n) {
        switch (id) {
            case ItemID::POTION:
                return new Potion(n);
            case ItemID::SUPER_POTION:
                return new SuperPotion(n);
            case ItemID::HYPER_POTION:
                return new HyperPotion(n);
            case ItemID::ETHER:
                return new Ether(n);
            case ItemID::ANTIDOTE:
                return new Antidote(n);
            case ItemID::AWAKENING:
                return new Awakening(n);
            case ItemID::BURN_HEAL:
                return new BurnHeal(n);
            case ItemID::ICE_HEAL:
                return new IceHeal(n);
            case ItemID::PARALYZE_HEAL:
                return new ParalyzeHeal(n);
            case ItemID::POKE_BALL:
                return new PokeBall(n);
            case ItemID::GREAT_BALL:
                return new GreatBall(n);
            case ItemID::ULTRA_BALL:
                return new UltraBall(n);
            case ItemID::MASTER_BALL:
                return new MasterBall(n);
            case ItemID::X_ATTACK:
                return new XAttack(n);
            case ItemID::X_DEFENSE:
                return new XDefense(n);
            case ItemID::X_SP_ATTACK:
                return new XSpAttack(n);
            case ItemID::X_SP_DEFENSE:
                return new XSpDefense(n);
            case ItemID::X_SPEED:
                return new XSpeed(n);
            case ItemID::X_ACCURACY:
                return new XAccuracy(n);
            default:
                return nullptr;
        }
    }
}
