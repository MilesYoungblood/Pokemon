//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/StatusItem.h"

struct Antidote : public StatusItem {
    explicit Antidote(int quantity) : StatusItem(quantity, "Antidote", Status::POISON) {}
};

struct Awakening : public StatusItem {
    explicit Awakening(int quantity) : StatusItem(quantity, "Awakening", Status::SLEEP) {}
};

struct BurnHeal : public StatusItem {
    explicit BurnHeal(int quantity) : StatusItem(quantity, "Burn Heal", Status::BURN) {}
};

struct IceHeal : public StatusItem {
    explicit IceHeal(int quantity) : StatusItem(quantity, "Ice Heal", Status::FREEZE) {}
};

struct ParalyzeHeal : public StatusItem {
    explicit ParalyzeHeal(int quantity) : StatusItem(quantity, "Paralyze Heal", Status::PARALYSIS) {}
};
