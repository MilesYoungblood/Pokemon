//
// Created by Miles Youngblood on 10/8/2023.
//

#pragma once

#include <SDL.h>
#include <SDL_image.h>

struct TextureManager {
    static SDL_Texture * LoadTexture(const char *texture, SDL_Renderer *r);
    static void Draw(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect dest);
};
