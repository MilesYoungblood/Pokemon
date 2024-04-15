//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../Scene.h"

class TitleScreen final : public Scene {
public:
    void update() override;

    void render() override;

private:
    friend class Scene;

    TitleScreen() = default;
};
