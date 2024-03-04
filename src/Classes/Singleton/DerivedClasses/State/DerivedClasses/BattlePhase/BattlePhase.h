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
        MAIN,
        FIGHT,
        ACTION,
        T_OUT
    };
    std::stack<BattlePhase::BattleState> states{{ BattlePhase::BattleState::MAIN }};

    const std::array<std::function<void()>, 4> INIT_FUNCTIONS{
            [this] -> void { this->initMain(); },
            [this] -> void { this->initFight(); },
            [] -> void {},
            [] -> void {}
    };

    const std::array<std::function<void()>, 4> UPDATE_FUNCTIONS{
            [] -> void {},
            [] -> void {},
            [] -> void {},
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

    BattlePhase() = default;

    void initMain();

    void initFight();

    void engage(Trainer *attacker, Trainer *defender, int move, bool *skip);

    void preStatus(bool isUserFaster);

    void postStatus(bool isUserFaster);

    void handleTurn();

    void updateTOut();

public:
    void init(Trainer *trainer);

    void update() override;

    void render() override;
};
