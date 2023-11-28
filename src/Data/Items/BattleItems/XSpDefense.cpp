//
// Created by Miles on 11/27/2023.
//

#include "BattleItems.h"

namespace {
    void init() {
        battleItems.insert({ BattleItem::Id::X_SP_DEFENSE, {
                "X Sp. Defense",
                Pokemon::Stat::SP_DEFENSE,
        }});
    }

    bool invoke{ (init(), true) };
}
