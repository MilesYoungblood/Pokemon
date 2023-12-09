//
// Created by Miles Youngblood on 12/8/2023.
//

#pragma once

#include "../../Graphic.h"

class Button : public Graphic {
public:
    Button(SDL_Color  /*fg*/, SDL_Color  /*bg*/);

    void update() override;

    void render() const override;

    void onClick();

    void onHover();
};
