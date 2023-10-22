//
// Created by Miles Youngblood on 10/8/2023.
//

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class TextureManager {
private:
    static SDL_Renderer *renderer;

public:
    TextureManager() = default;
    explicit TextureManager(SDL_Renderer *r);
    static auto LoadTexture(const std::string &texture) -> SDL_Texture *;
    static void Draw(SDL_Texture *texture, SDL_Rect dest);
};
