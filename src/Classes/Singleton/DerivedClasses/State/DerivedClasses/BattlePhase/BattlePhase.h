//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../../../../Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "../../State.h"

class BattlePhase : public State {
private:
    enum class BattleState : Uint8 {
        MAIN
    };
    BattlePhase::BattleState currentState{ BattleState::MAIN };

    const std::array<std::function<void()>, 1> INIT_FUNCTIONS{
            BattlePhase::initMain
    };
    const std::array<std::function<void()>, 1> RENDER_FUNCTIONS{
            BattlePhase::renderMain
    };

    Entity *opponent{ nullptr };
    std::size_t turn{ 0 };

    bool skipPlayer{ false };
    bool skipOpponent{ false };

    bool isRunning{ true };

    friend class State;

    BattlePhase() = default;

    static void initMain();

    static void renderMain();

public:
    void init();

    void update() override;

    void render() override;
};
