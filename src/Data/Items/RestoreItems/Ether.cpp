//
// Created by Miles on 11/26/2023.
//

#include "RestoreItems.h"

namespace {
    void init() {
        restoreItems.insert({ RestoreItem::Id::ETHER, {
                "Ether",
                5,
                false
        }});
    }

    bool invoke{ (init(), true) };
}
