//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../Singleton.h"

class State : public Singleton<State> {
protected:
    State() = default;

public:
    enum class Id : Uint8 {
        TITLE_SCREEN, OVERWORLD, BATTLE
    };

    State(const State &) = delete;

    State(State &&) noexcept = delete;

    State &operator=(const State &) = delete;

    State &operator=(State &&) noexcept = delete;

    ~State() override = default;

    template<typename Derived>
    inline static Derived &getInstance() {
        static Derived state;
        return state;
    }

    virtual void update() = 0;

    virtual void render() = 0;
};
