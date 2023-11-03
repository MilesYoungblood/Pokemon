//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/DerivedClasses/StatusItem/StatusItem.h"

struct Antidote : public StatusItem {
    explicit Antidote(int n) : StatusItem(n) {}

    [[nodiscard]] Status getStatus() const override {
        return Status::POISON;
    }

    [[nodiscard]] ItemID getID() const override {
        return ItemID::ANTIDOTE;
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

    [[nodiscard]] ItemID getID() const override {
        return ItemID::AWAKENING;
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

    [[nodiscard]] ItemID getID() const override {
        return ItemID::BURN_HEAL;
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

    [[nodiscard]] ItemID getID() const override {
        return ItemID::ICE_HEAL;
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

    [[nodiscard]] ItemID getID() const override {
        return ItemID::PARALYZE_HEAL;
    }

    [[nodiscard]] std::string getName() const override {
        return "Paralyze Heal";
    }
};
