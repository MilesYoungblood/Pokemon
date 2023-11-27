//
// Created by Miles on 11/26/2023.
//

#include "RestoreItems.h"

namespace {
    void init() {
        restoreItems.insert({ RestoreItem::Id::HYPER_POTION, {
                "Hyper Potion",
                120,
                true
        }});
    }

    bool invoke{ (init(), true) };
}
