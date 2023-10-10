//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../Classes/Trainer/Trainer.h"

class Player : public Trainer {
private:
    static Player * instancePtr;
    static Pokemon *pc[12][30];
    explicit Player(int xPos, int yPos);

public:
    static Player* getPlayer(int xPos, int yPos);
    static void destroyPlayer();

    static void addToPC(Pokemon *toAdd);

    explicit operator bool() const override;
    bool canFight() const override;
};
