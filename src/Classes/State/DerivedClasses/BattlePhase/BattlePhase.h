//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../State.h"
#include "../../../Singleton/Singleton.h"

class BattlePhase : public State, public Singleton<BattlePhase> {
private:
    friend class Singleton<BattlePhase>;

    BattlePhase() = default;

public:
    void update() override;

    void render() override;
};