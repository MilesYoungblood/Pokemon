//
// Created by Miles on 10/5/2023.
//

#pragma once

#include "../../Data/ItemList.h"

namespace ItemFactory {
    Item *getItem(ItemID id, int n) {
        switch (id) {
            case POTION:
                return new Potion(n);
            case SUPER_POTION:
                return new SuperPotion(n);
            case HYPER_POTION:
                return new HyperPotion(n);
            case ETHER:
                return new Ether(n);
            case ANTIDOTE:
                return new Antidote(n);
            case AWAKENING:
                return new Awakening(n);
            case BURN_HEAL:
                return new BurnHeal(n);
            case ICE_HEAL:
                return new IceHeal(n);
            case PARALYZE_HEAL:
                return new ParalyzeHeal(n);
            case POKE_BALL:
                return new PokeBall(n);
            case GREAT_BALL:
                return new GreatBall(n);
            case ULTRA_BALL:
                return new UltraBall(n);
            case MASTER_BALL:
                return new MasterBall(n);
            case X_ATTACK:
                return new XAttack(n);
            case X_DEFENSE:
                return new XDefense(n);
            case X_SP_ATTACK:
                return new XSpAttack(n);
            case X_SP_DEFENSE:
                return new XSpDefense(n);
            case X_SPEED:
                return new XSpeed(n);
            case X_ACCURACY:
                return new XAccuracy(n);
            default:
                return nullptr;
        }
    }
}