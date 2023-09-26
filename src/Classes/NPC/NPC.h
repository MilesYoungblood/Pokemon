//
// Created by Miles Youngblood on 7/7/2023.
//

#pragma once

#include "../Trainer/Trainer.h"

class Map;

class NPC : public Trainer {
private:
    bool defeated;  // has this trainer been defeated (necessary to know if you can walk in LoS again)

public:
    NPC();
    NPC(const std::initializer_list<Pokemon*> &pokemon, int x, int y, int range);
    ~NPC();
    NPC& operator=(const NPC &rhs);

    //bool isInRange(const Trainer &t);
    bool isDefeated() const;
    void defeat() override;
    void moveToPlayer(const Map &map, const Trainer &trainer);
};