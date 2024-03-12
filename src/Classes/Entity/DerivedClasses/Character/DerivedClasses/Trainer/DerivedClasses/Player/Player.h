//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../Trainer.h"

class Player : public Trainer {
private:
    using box = std::array<std::array<std::unique_ptr<Pokemon>, 6>, 5>;
    std::array<box, 12> pc;

    int numFainted{ 0 };

    Player();

public:
    static Player &getPlayer();

    void addToPc(std::unique_ptr<Pokemon> toAdd);

    [[nodiscard]] bool canMoveForward(gsl::owner<Map *> map) const override;

    void handleFaint() override;

    void walk() override;

    void idle() override;

    [[nodiscard]] std::vector<std::string> winMessage() const override;

    [[nodiscard]] bool canFight() const override;
};
