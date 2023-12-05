//
// Created by Miles on 11/26/2023.
//

#include "StatusItems.h"

namespace {
    void init() {
        statusItems.insert({ StatusItem::Id::AWAKENING, {
                "Awakening",
                StatusCondition::SLEEP,
        }});
    }

    bool invoke{ (init(), true) };
}
