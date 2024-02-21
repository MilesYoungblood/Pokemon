//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../State.h"

class BattlePhase : public State {
private:
    friend class State;

    BattlePhase() = default;

public:
    void update() override;

    void render() override;
};
