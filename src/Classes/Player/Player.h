//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../Classes/Trainer/Trainer.h"

class Player : public Trainer {
private:
    static Player * instancePtr;
    Player();

public:
    static Player* getPlayer();
    static void destroyPlayer();
};
