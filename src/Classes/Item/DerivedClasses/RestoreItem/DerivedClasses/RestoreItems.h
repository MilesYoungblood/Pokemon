//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../RestoreItem.h"

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

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::ETHER;
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

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::POTION;
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

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::SUPER_POTION;
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

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::HYPER_POTION;
    }
};
