//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../Classes/Trainer/Trainer.h"

class Player : public Trainer {
private:
    static Player * instancePtr;
    Player(int x, int y);

public:
    static Player* getPlayer(int x, int y);
    static void destroyPlayer();
};
