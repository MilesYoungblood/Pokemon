//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../Trainer.h"

class Player : public Trainer {
private:
    std::array<std::array<std::unique_ptr < Pokemon>, 30>, 12> pc;

    Player() = default;

public:
    static Player &getPlayer();

    void init(const char *name, int x, int y, Direction direction);

    void addToPc(std::unique_ptr<Pokemon> toAdd);

    void walk() override;

    void idle() override;

    [[nodiscard]] bool canFight() const override;
};
