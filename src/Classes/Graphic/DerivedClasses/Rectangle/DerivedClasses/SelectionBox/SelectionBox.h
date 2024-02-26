//
// Created by Miles Youngblood on 2/3/2024.
//

#pragma once

#include "../../Rectangle.h"

class SelectionBox : public Rectangle {
private:
    std::vector<std::string> options;
    std::vector<void (*)()> functions;
    int current{ 0 };

public:
    SelectionBox(SDL_Rect dest, SDL_Color fg, int borderSize, const std::vector<std::string> &options);

    SelectionBox(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize, const std::vector<std::string> &options);

    void update() override;

    void render() const override;
};
