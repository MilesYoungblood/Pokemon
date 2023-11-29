//
// Created by Miles Youngblood on 11/29/2023.
//

#include "MoveList.h"

namespace {
    void init() {
        moveLookupTable.insert({ Move::Id::AIR_SLASH, {
                "Air Slash",
                "The user attacks with a blade of air that slices even the sky. It may also make the target flinch.",
                75,
                95,
                Type::FLYING,
                Move::Category::SPECIAL,
                false,
                false
        }});
    }

    bool invoke{ (init(), true) };
}
