//
// Created by Miles Youngblood on 10/8/2023.
//

#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *texture, SDL_Renderer *r) {
    SDL_Surface *temp = IMG_Load(texture);
    SDL_Texture *text = SDL_CreateTextureFromSurface(r, temp);
    SDL_FreeSurface(temp);

    return text;
}

void TextureManager::Draw(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect dest) {
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}
