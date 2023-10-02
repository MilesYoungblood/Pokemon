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
    NPC(const std::vector<Pokemon*> &pokemon, int x, int y, int range);\
    NPC(const NPC &toCopy);
    ~NPC();
    NPC& operator=(const NPC &rhs);

    bool canFight() const override;
    void defeat() override;
    void moveToPlayer(const Map &map, const Trainer &trainer);
};