//
// Created by Miles Youngblood on 7/14/2023.
//

#pragma once

#include "../../Classes/Item/RestoreItem.h"

struct Ether : public RestoreItem {
    explicit Ether(int quantity) : RestoreItem(quantity, 5, "Ether", "PP") {}
};