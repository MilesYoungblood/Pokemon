//
// Created by Miles Youngblood on 7/7/2023.
//

#pragma once

#include "../Trainer/Trainer.h"

class NPC : public Trainer {
private:
    int range;      // line of sight
    bool defeated;  // has this trainer been defeated

public:
    NPC(const std::initializer_list<Pokemon> &pokemon, int x, int y, int range);
    bool isInRange(const Trainer &t);
    bool isDefeated() const;
    void defeat();
    void moveToPlayer(Trainer t);
};