//
// Created by Miles on 11/26/2023.
//

#include "RestoreItems.h"

namespace {
    void init() {
        restoreItems.insert({ RestoreItem::Id::MAX_ETHER, {
                "Max Ether",
                std::numeric_limits<int>::max(),
                false
        }});
    }

    bool invoke{ (init(), true) };
}
