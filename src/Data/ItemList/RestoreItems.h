//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/DerivedClasses/RestoreItem/RestoreItem.h"

struct Ether : public RestoreItem {
    explicit Ether(int n) : RestoreItem("Ether", n, 5, RestoreType::PP) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::ETHER;
    }
};

struct Potion : public RestoreItem {
    explicit Potion(int n) : RestoreItem("Potion", n, 20, RestoreType::HP) {};

    [[nodiscard]] ItemID getID() const override {
        return ItemID::POTION;
    }
};

struct SuperPotion : public RestoreItem {
    explicit SuperPotion(int n) : RestoreItem("Super Potion", n, 60, RestoreType::HP) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::SUPER_POTION;
    }
};

struct HyperPotion : public RestoreItem {
    explicit HyperPotion(int n) : RestoreItem("Hyper Potion", n, 120, RestoreType::HP) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::HYPER_POTION;
    }
};
