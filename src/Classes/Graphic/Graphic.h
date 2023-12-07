//
// Created by Miles Youngblood on 12/5/2023.
//

#pragma once

class Graphic {
private:

public:
    virtual ~Graphic() = default;

    virtual void render() {};
};

class Button : public Graphic {
public:
    Button(SDL_Color fg, SDL_Color bg) {}

    void onClick() {}

    void onHover() {}
};