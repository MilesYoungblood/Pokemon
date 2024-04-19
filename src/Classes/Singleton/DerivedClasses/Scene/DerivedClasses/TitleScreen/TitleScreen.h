//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../Scene.h"

class TitleScreen final : public Scene {
public:
    void init() override;

    void fadeIn() override;

    void update() override;

    void fadeOut() override;

    void render() const override;

private:
    friend class Scene;

    TitleScreen() = default;
};
