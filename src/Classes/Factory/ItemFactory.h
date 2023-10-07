//
// Created by Miles on 10/5/2023.
//

#pragma once

#include "../../Data/ItemList.h"

namespace ItemFactory {
    Item *getItem(ItemID id) {
        switch (id) {
            case POTION:
                break;
            case SUPER_POTION:
                break;
            case HYPER_POTION:
                break;
            case ETHER:
                break;
            case ANTIDOTE:
                break;
            case AWAKENING:
                break;
            case BURN_HEAL:
                break;
            case ICE_HEAL:
                break;
            case PARALYZE_HEAL:
                break;
            case POKE_BALL:
                break;
            case GREAT_BALL:
                break;
            case ULTRA_BALL:
                break;
            case X_ATTACK:
                break;
            case X_SPEED:
                break;
            default:
                return nullptr;
        }
    }
}