//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../RestoreItem.h"

struct Ether : public RestoreItem {
    Ether() = default;

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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::ETHER;
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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::POTION;
    }
};

struct SuperPotion : public RestoreItem {
    SuperPotion() = default;

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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::SUPER_POTION;
    }
};

struct HyperPotion : public RestoreItem {
    HyperPotion() = default;

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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::HYPER_POTION;
    }
};
