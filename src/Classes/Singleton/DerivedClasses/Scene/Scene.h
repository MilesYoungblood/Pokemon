//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../Singleton.h"

class Scene : public Singleton<Scene> {
public:
    enum class Id : Uint8 {
        TITLE_SCREEN, OVERWORLD, BATTLE
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

    static void pushEvent();

    virtual void handleEvents();

    virtual void update() = 0;

    virtual void render() const = 0;

protected:
    Scene() = default;

    bool pollEvent();

    bool waitEvent();

    [[nodiscard]] SDL_EventType getEventType() const;

private:
    SDL_Event event{};
};
