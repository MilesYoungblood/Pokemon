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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::ANTIDOTE;
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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::AWAKENING;
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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::BURN_HEAL;
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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::ICE_HEAL;
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

    [[nodiscard]] Item::Id getId() const override {
        return Item::Id::PARALYZE_HEAL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Paralyze Heal";
    }
};
