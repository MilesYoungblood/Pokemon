//
// Created by Miles Youngblood on 7/7/2023.
//

#pragma once

#include "../Trainer/Trainer.h"

class Map;

class NPC : public Trainer {
private:
    bool canBattle;  // has this trainer been defeated (necessary to know if you can walk in LoS again)

public:
    NPC(const std::vector<Pokemon*> &pokemon, int x, int y, int range);\
    NPC(const NPC &toCopy) = delete;
    NPC& operator=(const NPC &rhs) = delete;

    explicit operator bool() const override;
    bool canFight() const;
    void setBattleStatus(bool flag);

    void defeat() override;
    void moveToPlayer(const Map &map, const Trainer &trainer);
};