//
// Created by Miles on 11/27/2023.
//

#include "BattleItems.h"

namespace {
    void init() {
        battleItems.insert({ BattleItem::Id::X_ACCURACY, {
                "X Accuracy",
                Pokemon::Stat::ACCURACY,
        }});
    }

    bool invoke{ (init(), true) };
}
