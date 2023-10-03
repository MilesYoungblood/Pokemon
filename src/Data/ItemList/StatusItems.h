//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/StatusItem.h"

struct Antidote : public StatusItem {
    explicit Antidote(int n) : StatusItem(n, "Antidote", Status::POISON) {}
};

struct Awakening : public StatusItem {
    explicit Awakening(int n) : StatusItem(n, "Awakening", Status::SLEEP) {}
};

struct BurnHeal : public StatusItem {
    explicit BurnHeal(int n) : StatusItem(n, "Burn Heal", Status::BURN) {}
};

struct IceHeal : public StatusItem {
    explicit IceHeal(int n) : StatusItem(n, "Ice Heal", Status::FREEZE) {}
};

struct ParalyzeHeal : public StatusItem {
    explicit ParalyzeHeal(int n) : StatusItem(n, "Paralyze Heal", Status::PARALYSIS) {}
};
