//
// Created by Miles on 11/26/2023.
//

#include "StatusItems.h"

namespace {
    void init() {
        statusItems.insert({ StatusItem::Id::BURN_HEAL, {
                "Burn Heal",
                StatusCondition::BURN,
        }});
    }

    bool invoke{ (init(), true) };
}
