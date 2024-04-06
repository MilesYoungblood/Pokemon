//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../Scene.h"

class TitleScreen : public Scene {
private:
    friend class Scene;

    TitleScreen() = default;

public:
    void update() override;

    void render() override;
};
