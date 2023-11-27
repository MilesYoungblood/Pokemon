//
// Created by Miles on 11/26/2023.
//


#include "RestoreItems.h"

namespace {
    void init() {
        restoreItems.insert({ RestoreItem::Id::MAX_POTION, {
                "Max Potion",
                std::numeric_limits<int>::max(),
                true
        }});
    }

    bool invoke{ (init(), true) };
}
