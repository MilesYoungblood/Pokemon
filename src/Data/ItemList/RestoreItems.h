//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/RestoreItem.h"

struct Ether : public RestoreItem {
    explicit Ether(int n) : RestoreItem(n, 5, "Ether", RestoreType::PP) {}
};

struct Potion : public RestoreItem {
    explicit Potion(int n) : RestoreItem(n, 20, "Potion", RestoreType::HP) {};
};

struct SuperPotion : public RestoreItem {
    explicit SuperPotion(int n) : RestoreItem(n, 60, "Super Potion", RestoreType::HP) {}
};

struct HyperPotion : public RestoreItem {
    explicit HyperPotion(int n) : RestoreItem(n, 120, "Hyper Potion", RestoreType::HP) {}
};
