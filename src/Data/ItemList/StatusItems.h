//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/DerivedClasses/StatusItem/StatusItem.h"

struct Antidote : public StatusItem {
    explicit Antidote(int n) : StatusItem("Antidote", n, Status::POISON) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::ANTIDOTE;
    }
};

struct Awakening : public StatusItem {
    explicit Awakening(int n) : StatusItem("Awakening", n, Status::SLEEP) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::AWAKENING;
    }
};

struct BurnHeal : public StatusItem {
    explicit BurnHeal(int n) : StatusItem("Burn Heal", n, Status::BURN) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::BURN_HEAL;
    }
};

struct IceHeal : public StatusItem {
    explicit IceHeal(int n) : StatusItem("Ice Heal", n, Status::FREEZE) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::ICE_HEAL;
    }
};

struct ParalyzeHeal : public StatusItem {
    explicit ParalyzeHeal(int n) : StatusItem("Paralyze Heal", n, Status::PARALYSIS) {}

    [[nodiscard]] ItemID getID() const override {
        return ItemID::PARALYZE_HEAL;
    }
};
