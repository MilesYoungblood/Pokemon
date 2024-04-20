//
// Created by miles on 4/19/2024.
//

#pragma once

#include "../../Singleton.h"

class EventHandler final : public Singleton<EventHandler> {
public:
    bool pollEvent();

    bool waitEvent();

    static void pushEvent();

    [[nodiscard]] SDL_EventType getEventType() const;

private:
    SDL_Event event{};
};
