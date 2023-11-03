//
// Created by Miles Youngblood on 10/8/2023.
//

#pragma once

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

// responsible for creating textures and drawing to the renderer
class TextureManager {
private:
    SDL_Renderer *textureRenderer = nullptr;

    inline static TextureManager *instancePtr = nullptr;

    inline static bool isInitialized = false;

    TextureManager() = default;

public:
    static TextureManager *getInstance() {
        if (TextureManager::instancePtr == nullptr) {
            TextureManager::instancePtr = new TextureManager();
            std::cout << "TextureManager instance created!\n";
        }
        return TextureManager::instancePtr;
    }

    static void deleteInstance() {
        delete TextureManager::instancePtr;
        TextureManager::instancePtr = nullptr;
        TextureManager::isInitialized = false;

        std::cout << "TextureManager instance deleted!\n";
    }

    void init(SDL_Renderer *renderer) {
        // only allow this function to be called once per instantiation of TextureManager object
        if (TextureManager::isInitialized) {
            return;
        }
        this->textureRenderer = renderer;
        TextureManager::isInitialized = true;
    }

    [[nodiscard]] static bool wasInitialized() {
        return TextureManager::isInitialized;
    }

    SDL_Texture *loadTexture(std::string_view texture) {
        return IMG_LoadTexture(this->textureRenderer, texture.data());
    }

    SDL_Texture *loadText(TTF_Font *font, const char *text, SDL_Color fg) {
        SDL_Surface *temp = TTF_RenderText_Solid(font, text, fg);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);
        SDL_FreeSurface(temp);

        return texture;
    }

    SDL_Texture *loadText(TTF_Font *font, std::string_view text, SDL_Color fg) {
        SDL_Surface *temp = TTF_RenderText_Solid(font, text.data(), fg);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);
        SDL_FreeSurface(temp);

        return texture;
    }

    void draw(SDL_Texture *texture, SDL_Rect dest) {
        SDL_RenderCopy(this->textureRenderer, texture, nullptr, &dest);
    }
};
