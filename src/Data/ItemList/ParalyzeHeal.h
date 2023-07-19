//
// Created by Miles Youngblood on 7/15/2023.
//

#pragma once

#include "../../Classes/Item/StatusItem.h"

struct ParalyzeHeal : public StatusItem {
    explicit ParalyzeHeal(int quantity) : StatusItem(quantity, "Paralyze Heal", "paralysis") {}
};