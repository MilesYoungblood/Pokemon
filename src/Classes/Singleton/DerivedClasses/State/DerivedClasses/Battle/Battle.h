//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../../../../Graphic/DerivedClasses/Rectangle/DerivedClasses/Button/Button.h"
#include "../../../../../Entity/DerivedClasses/Character/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "../../State.h"

class Battle : public State {
private:
    enum class BattleState : Uint8 {
        MAIN,
        SELECT_MOVE,
        ENGAGE,
        T_OUT
    };
    std::deque<Battle::BattleState> states{ Battle::BattleState::MAIN };

    const std::array<std::function<void()>, 4> INIT_FUNCTIONS{
            [this] -> void { this->initMain(); },
            [this] -> void { this->initFight(); },
            Battle::initEngage,
            nullptr
    };

    const std::array<std::function<void()>, 4> UPDATE_FUNCTIONS{
            nullptr,
            nullptr,
            [this] -> void { this->updateEngage(); },
            [this] -> void { this->updateTOut(); }
    };

    Trainer *opponent{ nullptr };
    std::size_t turn{ 0 };

    bool skipPlayer{ false };
    bool skipOpponent{ false };

    int playerMove{ 0 };
    int opponentMove{ 0 };

    bool isRunning{ true };

    friend class State;

    Battle() = default;

    void initMain();

    void initFight();

    static void initEngage();

    void engage(Trainer *attacker, Trainer *defender, int move, bool *skip);

    void preStatus(bool isPlayerFaster);

    void postStatus(bool isPlayerFaster);

    void handleTurn();

    void updateEngage();

    void updateTOut();

public:
    void init(Trainer *trainer);

    void update() override;

    void render() override;
};
