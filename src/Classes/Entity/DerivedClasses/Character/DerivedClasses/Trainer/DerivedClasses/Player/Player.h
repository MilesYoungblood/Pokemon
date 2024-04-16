//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../Trainer.h"

class Player final : public Trainer {
public:
    static Player &getPlayer();

    [[maybe_unused]] void addToPc(std::unique_ptr<Pokemon> toAdd);

    [[nodiscard]] bool canMoveForward(const Map &map) const override;

    void handleFaint() override;

    void handleSwitchOut(bool *renderSelf) override;

    void handleVictory() override;

    [[nodiscard]] std::vector<std::string> winMessage(const Trainer *trainer) const override;

    [[nodiscard]] bool canFight() const override;

private:
    using box = std::array<std::array<std::unique_ptr<Pokemon>, 6>, 5>;
    std::array<box, 12> pc;

    int numFainted{ 0 };

    Player();

    void handleMove(SDL_Scancode scancode);

    void handleReturn() const;

    void interact() override;

    void walk() override;

    void idle() override;
};
