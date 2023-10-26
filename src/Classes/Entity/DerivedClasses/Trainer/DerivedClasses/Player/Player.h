//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../Trainer.h"

class Player : public Trainer {
private:
    static Player *instancePtr;
    static std::array<std::array<Pokemon *, 30>, 12> pc;
    Player(int x, int y, int direction);

public:
    static Player * getPlayer(int x = 6, int y = 8, int direction = 2);
    static void destroyPlayer();

    static void addToPC(Pokemon *toAdd);

    explicit operator bool() const override;
    [[nodiscard]] bool canFight() const override;
};
