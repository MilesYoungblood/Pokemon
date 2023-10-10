//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../Classes/Trainer/Trainer.h"

class Player : public Trainer {
private:
    static Player * instancePtr;
    static Pokemon *pc[12][30];
    explicit Player(SDL_Renderer *renderer, int mapX, int mapY);

public:
    static Player* getPlayer(SDL_Renderer *renderer, int mapX, int mapY);
    static void destroyPlayer();

    static void addToPC(Pokemon *toAdd);

    explicit operator bool() const override;
    bool canFight() const override;
};
