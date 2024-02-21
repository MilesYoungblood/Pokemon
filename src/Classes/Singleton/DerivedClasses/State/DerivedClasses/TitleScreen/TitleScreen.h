//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../State.h"

class TitleScreen : public State {
private:
    friend class State;

    TitleScreen() = default;

public:
    void update() override;

    void render() override;
};
