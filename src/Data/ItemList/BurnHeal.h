//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/StatusItem.h"

struct BurnHeal : public StatusItem {
    BurnHeal(int quantity) : StatusItem(quantity, "Burn Heal", "burn") {}
};