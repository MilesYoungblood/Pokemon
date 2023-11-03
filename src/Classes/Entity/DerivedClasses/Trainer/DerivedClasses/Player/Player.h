//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../Trainer.h"

class Player : public Trainer {
private:
    static Player *instancePtr;
    static std::array<std::array<std::unique_ptr<Pokemon>, 30>, 12> pc;

    Player(const char *name, int x, int y, Direction direction);

public:
    static Player *getPlayer(const char *name = "Hilbert", int x = 6, int y = 8, Direction direction = Direction::DOWN);

    static void destroyPlayer();

    static void addToPc(std::unique_ptr<Pokemon> toAdd);

    explicit operator bool() const override;

    [[nodiscard]] bool canFight() const override;
};
