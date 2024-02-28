//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../../../../Graphic/DerivedClasses/Rectangle/DerivedClasses/Button/Button.h"
#include "../../../../../Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "../../State.h"

class BattlePhase : public State {
private:
    enum class BattleState : Uint8 {
        MAIN
    };
    BattlePhase::BattleState currentState{ BattleState::MAIN };

    const std::array<std::function<void()>, 1> INIT_FUNCTIONS{
            [this] -> void { this->initMain(); }
    };
    const std::array<std::function<void()>, 1> RENDER_FUNCTIONS{
            [] -> void {}
    };

    Trainer *opponent{ nullptr };
    std::size_t turn{ 0 };

    bool skipPlayer{ false };
    bool skipOpponent{ false };
    bool canRunAway{ false };

    bool isRunning{ true };

    friend class State;

    BattlePhase() = default;

    void initMain();

public:
    void init(Trainer *trainer, bool isTrainer);

    void update() override;

    void render() override;
};
