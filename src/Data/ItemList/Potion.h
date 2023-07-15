//
// Created by Miles Youngblood on 7/14/2023.
//

#pragma once

#include "../../Classes/Item/RestoreItem.h"

struct Potion : public RestoreItem {
    explicit Potion(int quantity) : RestoreItem(quantity, 20, "Potion", "HP") {};
};