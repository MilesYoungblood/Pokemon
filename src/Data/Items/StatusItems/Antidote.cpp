//
// Created by Miles on 11/26/2023.
//

#include "StatusItems.h"

namespace {
    void init() {
        statusItems.insert({ StatusItem::Id::ANTIDOTE, {
                "Antidote",
                StatusCondition::POISON,
        }});
    }

    bool invoke{ (init(), true) };
}
