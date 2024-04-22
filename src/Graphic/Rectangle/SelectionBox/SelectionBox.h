//
// Created by Miles Youngblood on 2/3/2024.
//

#pragma once

#include "../../Texture/Texture.h"
#include "../Rectangle.h"

class SelectionBox final : public Rectangle {
public:
    SelectionBox(SDL_Rect dest, int borderSize, const std::vector<std::pair<std::string, std::function<void()>>> &options);

    void update() override;

    void render() const override;

private:
    const int maxVisible;
    int current{ 0 };
    int topVisible{ 0 };

    std::vector<std::pair<std::string, std::function<void()>>> options;

    Texture arrow{};

    void updateArrow();
};
