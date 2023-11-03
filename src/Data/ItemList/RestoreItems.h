//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/DerivedClasses/RestoreItem/RestoreItem.h"

struct Ether : public RestoreItem {
    explicit Ether(int n) : RestoreItem(n) {}

    [[nodiscard]] std::string getName() const override {
        return "Ether";
    }

    [[nodiscard]] int getAmount() const override {
        return 5;
    }

    [[nodiscard]] bool isHp() const override {
        return false;
    }

    [[nodiscard]] ItemID getID() const override {
        return ItemID::ETHER;
    }
};

struct Potion : public RestoreItem {
    explicit Potion(int n) : RestoreItem(n) {};

    [[nodiscard]] std::string getName() const override {
        return "Potion";
    }

    [[nodiscard]] int getAmount() const override {
        return 20;
    }

    [[nodiscard]] bool isHp() const override {
        return true;
    }

    [[nodiscard]] ItemID getID() const override {
        return ItemID::POTION;
    }
};

struct SuperPotion : public RestoreItem {
    explicit SuperPotion(int n) : RestoreItem(n) {}

    [[nodiscard]] std::string getName() const override {
        return "Super Potion";
    }

    [[nodiscard]] int getAmount() const override {
        return 60;
    }

    [[nodiscard]] bool isHp() const override {
        return true;
    }

    [[nodiscard]] ItemID getID() const override {
        return ItemID::SUPER_POTION;
    }
};

struct HyperPotion : public RestoreItem {
    explicit HyperPotion(int n) : RestoreItem(n) {}

    [[nodiscard]] std::string getName() const override {
        return "Hyper Potion";
    }

    [[nodiscard]] int getAmount() const override {
        return 120;
    }

    [[nodiscard]] bool isHp() const override {
        return true;
    }

    [[nodiscard]] ItemID getID() const override {
        return ItemID::HYPER_POTION;
    }
};
