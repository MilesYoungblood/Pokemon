//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../Singleton.h"

class Scene : public Singleton<Scene> {
public:
    enum class Id : Uint8 {
        TITLE_SCREEN, OVERWORLD, BATTLE
    };
    enum class State : Uint8 {
        FADED_IN, FADING_IN, RUNNING, FADING_OUT, FADED_OUT
    };

    Scene(const Scene &) = delete;

    Scene(Scene &&) noexcept = delete;

    Scene &operator=(const Scene &) = delete;

    Scene &operator=(Scene &&) noexcept = delete;

    ~Scene() override = default;

    template<typename Derived>
    static Derived &getInstance() {
        static Derived state;
        return state;
    }

    void setState(State x);

    [[nodiscard]] bool getState(State x) const;

    virtual void init() = 0;

    virtual void handleEvents();

    virtual void fadeIn() = 0;

    virtual void update() = 0;

    virtual void fadeOut() = 0;

    virtual void render() const = 0;

protected:
    Scene() = default;

private:
    State currentState{ State::RUNNING };
};
