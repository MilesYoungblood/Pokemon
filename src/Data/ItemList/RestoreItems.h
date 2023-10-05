//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/RestoreItem.h"

struct Ether : public RestoreItem {
    explicit Ether(int n) : RestoreItem("Ether", n, 5, RestoreType::PP) {}
};

struct Potion : public RestoreItem {
    explicit Potion(int n) : RestoreItem("Potion", n, 20, RestoreType::HP) {};
};

struct SuperPotion : public RestoreItem {
    explicit SuperPotion(int n) : RestoreItem("Super Potion", n, 60, RestoreType::HP) {}
};

struct HyperPotion : public RestoreItem {
    explicit HyperPotion(int n) : RestoreItem("Hyper Potion", n, 120, RestoreType::HP) {}
};
