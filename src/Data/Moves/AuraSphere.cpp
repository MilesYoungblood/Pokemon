//
// Created by Miles Youngblood on 11/29/2023.
//

#include "MoveList.h"

namespace {
    void init() {
        moveLookupTable.insert({ Move::Id::AIR_SLASH, {
                "Aura Sphere",
                "The user looses a blast of aura power from deep within its body at the target. This move is certain to hit.",
                90,
                100,
                Type::FIGHTING,
                Move::Category::SPECIAL,
                false,
                true
        }});
    }

    bool invoke{ (init(), true) };
}
