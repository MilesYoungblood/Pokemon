//
// Created by Miles Youngblood on 2/3/2024.
//

#pragma once

#include "../../Rectangle.h"

class SelectionBox : public Rectangle {
private:
    std::vector<std::pair<std::string, std::function<void()>>> options;
    int current{ 0 };

public:
    SelectionBox(SDL_Rect dest, int borderSize, const std::vector<std::pair<std::string, std::function<void()>>> &options);

    SelectionBox(SDL_Rect dest, SDL_Color fg, int borderSize,
                 const std::vector<std::pair<std::string, std::function<void()>>> &options);

    SelectionBox(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize,
                 const std::vector<std::pair<std::string, std::function<void()>>> &options);

    void update() override;

    void render() const override;
};
