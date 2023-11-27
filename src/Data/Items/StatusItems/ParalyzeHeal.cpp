//
// Created by Miles on 11/26/2023.
//

#include "StatusItems.h"

namespace {
    void init() {
        statusItems.insert({ StatusItem::Id::PARALYZE_HEAL, {
                "Paralyze Heal",
                Status::PARALYSIS,
        }});
    }

    bool invoke{ (init(), true) };
}
