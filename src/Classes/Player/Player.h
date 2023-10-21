//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../Classes/Trainer/Trainer.h"

class Player : public Trainer {
private:
    static Player *instancePtr;
    static std::array<std::array<Pokemon *, 30>, 12> pc;
    Player();

public:
    static auto getPlayer() -> Player*;
    static void destroyPlayer();

    static void addToPC(Pokemon *toAdd);

    explicit operator bool() const override;
    [[nodiscard]] auto canFight() const -> bool override;
};
