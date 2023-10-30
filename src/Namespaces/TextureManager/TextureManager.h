//
// Created by Miles Youngblood on 10/8/2023.
//

#pragma once

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string_view>

// responsible for creating textures and drawing to the renderer
namespace TextureManager {
    inline SDL_Renderer *textureRenderer = nullptr;

    inline SDL_Texture *LoadTexture(std::string_view texture) {
        return IMG_LoadTexture(textureRenderer, texture.data());
    }

    inline SDL_Texture *LoadText(TTF_Font *font, const char *text, SDL_Color fg) {
        SDL_Surface *temp = TTF_RenderText_Solid(font, text, fg);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(textureRenderer, temp);
        SDL_FreeSurface(temp);

        return texture;
    }

    inline SDL_Texture *LoadText(TTF_Font *font, std::string_view text, SDL_Color fg) {
        SDL_Surface *temp = TTF_RenderText_Solid(font, text.data(), fg);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(textureRenderer, temp);
        SDL_FreeSurface(temp);

        return texture;
    }

    inline void Draw(SDL_Texture *texture, SDL_Rect dest) {
        SDL_RenderCopy(textureRenderer, texture, nullptr, &dest);
    }
}
