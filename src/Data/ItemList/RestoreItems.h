//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/RestoreItem.h"

struct Ether : public RestoreItem {
    explicit Ether(int quantity) : RestoreItem(quantity, 5, "Ether", RestoreType::PP) {}
};

struct Potion : public RestoreItem {
    explicit Potion(int quantity) : RestoreItem(quantity, 20, "Potion", RestoreType::HP) {};
};
