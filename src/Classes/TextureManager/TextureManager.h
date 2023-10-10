//
// Created by Miles Youngblood on 10/8/2023.
//

#pragma once

#include <SDL.h>
#include <SDL_image.h>

class TextureManager {
private:
    static SDL_Renderer *renderer;

public:
    explicit TextureManager(SDL_Renderer *r);
    static void EstablishRenderer(SDL_Renderer *r);
    static SDL_Texture * LoadTexture(const char *texture);
    static void Draw(SDL_Texture *texture, SDL_Rect dest);
};
