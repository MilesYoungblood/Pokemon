//
// Created by Miles on 1/28/2024.
//

#pragma once

class State {
protected:
    State() = default;

public:
    enum class Id : Uint8 {
        TITLE_SCREEN, OVERWORLD, BATTLE
    };

    State(const State &) = delete;

    State(State &&) noexcept = default;

    State &operator=(const State &) = delete;

    State &operator=(State &&) noexcept = default;

    virtual ~State() = default;

    virtual void update() = 0;

    virtual void render() = 0;
};
