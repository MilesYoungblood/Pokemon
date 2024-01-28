//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../State.h"
#include "../../../Singleton/Singleton.h"

class TitleScreen : public State, public Singleton<TitleScreen> {
private:
    friend class Singleton<TitleScreen>;

    TitleScreen() = default;

public:
    void update() override;

    void render() override;
};
