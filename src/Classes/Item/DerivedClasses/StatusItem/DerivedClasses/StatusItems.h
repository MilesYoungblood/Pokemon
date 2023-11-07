//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../StatusItem.h"

struct Antidote : public StatusItem {
    explicit Antidote(int n) : StatusItem(n) {}

    [[nodiscard]] Status getStatus() const override {
        return Status::POISON;
    }

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::ANTIDOTE;
    }

    [[nodiscard]] std::string getName() const override {
        return "Antidote";
    }
};

struct Awakening : public StatusItem {
    explicit Awakening(int n) : StatusItem(n) {}

    [[nodiscard]] Status getStatus() const override {
        return Status::SLEEP;
    }

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::AWAKENING;
    }

    [[nodiscard]] std::string getName() const override {
        return "Awakening";
    }
};

struct BurnHeal : public StatusItem {
    explicit BurnHeal(int n) : StatusItem(n) {}

    [[nodiscard]] Status getStatus() const override {
        return Status::BURN;
    }

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::BURN_HEAL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Burn Heal";
    }
};

struct IceHeal : public StatusItem {
    explicit IceHeal(int n) : StatusItem(n) {}

    [[nodiscard]] Status getStatus() const override {
        return Status::FREEZE;
    }

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::ICE_HEAL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Ice Heal";
    }
};

struct ParalyzeHeal : public StatusItem {
    explicit ParalyzeHeal(int n) : StatusItem(n) {}

    [[nodiscard]] Status getStatus() const override {
        return Status::PARALYSIS;
    }

    [[nodiscard]] Item::ID getID() const override {
        return Item::ID::PARALYZE_HEAL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Paralyze Heal";
    }
};
