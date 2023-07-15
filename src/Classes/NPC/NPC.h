//
// Created by Miles Youngblood on 7/7/2023.
//

#pragma once

#include "../Trainer/Trainer.h"

class Map;

class NPC : public Trainer {
private:
    bool defeated;  // has this trainer been defeated (necessary to know if you can walk in LOS again)

public:
    NPC(const std::initializer_list<Pokemon> &pokemon, int x, int y, int range);

    //bool isInRange(const Trainer &t);
    bool isDefeated() const;
    void defeat() override;
    void moveToPlayer(const Map &map, const Trainer &trainer, const std::vector<NPC> &npcArray);
};