//
// Created by Miles on 11/26/2023.
//

#include "StatusItems.h"

namespace {
    void init() {
        statusItems.insert({ StatusItem::Id::ICE_HEAL, {
                "Ice Heal",
                StatusCondition::FREEZE,
        }});
    }

    bool invoke{ (init(), true) };
}
