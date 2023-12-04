//
// Created by Miles Youngblood on 11/17/2023.
//

#pragma once

class GameComponent {
public:
    GameComponent() = default;

    GameComponent(const GameComponent &) = default;

    GameComponent(GameComponent &&) = default;

    GameComponent &operator=(const GameComponent &) = delete;

    GameComponent &operator=(GameComponent &&) = delete;

    virtual ~GameComponent() = default;
};
