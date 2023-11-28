//
// Created by Miles on 11/27/2023.
//

#include "BattleItems.h"

namespace {
    void init() {
        battleItems.insert({ BattleItem::Id::X_SP_ATTACK, {
                "X Sp. Attack",
                Pokemon::Stat::SP_ATTACK,
        }});
    }

    bool invoke{ (init(), true) };
}
