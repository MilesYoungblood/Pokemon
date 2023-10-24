//
// Created by Miles Youngblood on 10/8/2023.
//

#include "TextureManager.h"

SDL_Renderer *TextureManager::renderer = nullptr;

TextureManager::TextureManager(SDL_Renderer *r) {
    TextureManager::renderer = r;
}

SDL_Texture * TextureManager::LoadTexture(std::string_view texture) {
    SDL_Surface *temp = IMG_Load(texture.data());
    SDL_Texture *text = SDL_CreateTextureFromSurface(TextureManager::renderer, temp);
    SDL_FreeSurface(temp);

    return text;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect dest) {
    SDL_RenderCopy(TextureManager::renderer, texture, nullptr, &dest);
}
