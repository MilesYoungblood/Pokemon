//
// Created by Miles on 11/26/2023.
//

#include "RestoreItems.h"

namespace {
    void init() {
        restoreItems.insert({ RestoreItem::Id::POTION, {
                "Potion",
                20,
                true
        }});
    }

    bool invoke{ (init(), true) };
}
