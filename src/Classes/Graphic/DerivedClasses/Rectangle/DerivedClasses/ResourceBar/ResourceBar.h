//
// Created by Miles Youngblood on 2/6/2024.
//

#pragma once

#include "../../../../../Component/Resource/Resource.h"
#include "../../Rectangle.h"

class ResourceBar final : public Rectangle {
public:
    ResourceBar(SDL_Rect dest, SDL_Color fg, int borderSize, int amount);

    Component::Resource &getProgress();

    void update() override;

    void render() const override;

private:
    Component::Resource progress;
};
