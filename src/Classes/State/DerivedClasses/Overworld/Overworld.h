//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../State.h"
#include "../../../Singleton/Singleton.h"
#include "../../../Map/Map.h"

class Overworld : public State, public Singleton<Overworld> {
private:
    friend class Singleton<Overworld>;

    Overworld() = default;

public:
    void update() override;

    void render() override;
};
