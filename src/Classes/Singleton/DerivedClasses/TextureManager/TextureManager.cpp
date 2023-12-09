//
// Created by Miles on 11/28/2023.
//

#include "TextureManager.h"

void TextureManager::init(SDL_Renderer *renderer) {
    // only allow this function to be called once per instantiation of TextureManager object
    if (not this->isInitialized) {
        this->textureRenderer = renderer;
        this->isInitialized = true;
    }
}

SDL_Texture *TextureManager::loadTexture(const char *path) {
    return IMG_LoadTexture(this->textureRenderer, std::string_view("../assets/images/" + std::string(path)).data());
}

SDL_Texture *TextureManager::loadText(TTF_Font *font, const char *text, SDL_Color fg) {
    SDL_Surface *temp = TTF_RenderText_Solid(font, text, fg);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);
    SDL_FreeSurface(temp);

    return texture;
}

SDL_Texture *TextureManager::loadText(TTF_Font *font, std::string_view text, SDL_Color fg) {
    SDL_Surface *temp = TTF_RenderText_Solid(font, text.data(), fg);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);
    SDL_FreeSurface(temp);

    return texture;
}

void TextureManager::draw(SDL_Texture *texture, const SDL_Rect &dest) {
    SDL_RenderCopy(this->textureRenderer, texture, nullptr, &dest);
}

void TextureManager::drawFrame(SDL_Texture *texture, const SDL_Rect &dest, int frame, int row) {
    const SDL_Rect src{ dest.w * frame, dest.h * row, dest.w, dest.h };
    SDL_RenderCopy(this->textureRenderer, texture, &src, &dest);
}

void TextureManager::drawRect(const SDL_Rect &dest, SDL_Color fg, int pt) {
    SDL_Rect border{ dest.x - 1, dest.y - 1, dest.w + 2, dest.h + 2 };

    SDL_SetRenderDrawColor(this->textureRenderer, fg.r, fg.g, fg.b, fg.a);
    for (int i = 0; i < pt; ++i) {
        SDL_RenderDrawRect(this->textureRenderer, &border);
        --border.x;
        --border.y;
        border.w += 2;
        border.h += 2;
    }
}

void TextureManager::drawRect(const SDL_Rect &dest, SDL_Color fg, SDL_Color bg, int pt) {
    // draw the inner box
    SDL_SetRenderDrawColor(this->textureRenderer, fg.r, fg.g, fg.b, fg.a);
    SDL_RenderFillRect(this->textureRenderer, &dest);

    SDL_Rect border{ dest.x - 1, dest.y - 1, dest.w + 2, dest.h + 2 };

    // draw the border
    SDL_SetRenderDrawColor(this->textureRenderer, bg.r, bg.g, bg.b, bg.a);
    for (int i = 0; i < pt; ++i) {
        SDL_RenderDrawRect(this->textureRenderer, &border);
        --border.x;
        --border.y;
        border.w += 2;
        border.h += 2;
    }
}

void TextureManager::drawBorderedText(const char *text, int x, int y, int pt, SDL_Color fg, SDL_Color bg,
                                      TTF_Font *font) {
    SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, text, fg);
    if (textSurface == nullptr) {
        std::clog << "Error loading surface: " << SDL_GetError() << '\n';
        SDL_ClearError();
        return;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(this->textureRenderer, textSurface);
    if (textTexture == nullptr) {
        std::clog << "Error loading texture: " << SDL_GetError() << '\n';
        SDL_ClearError();

        SDL_FreeSurface(textSurface);
        std::terminate();
    }

    // Render text with outline by rendering text multiple times with slight offsets
    SDL_Rect destRect(x, y, textSurface->w, textSurface->h);

    // Draw the outline first
    SDL_SetTextureColorMod(textTexture, bg.r, bg.g, bg.b);
    for (int i = 1; i <= pt; ++i) {
        for (int dx = -i; dx <= i; ++dx) {
            for (int dy = -i; dy <= i; ++dy) {
                destRect.x = x + dx;
                destRect.y = y + dy;
                SDL_RenderCopy(this->textureRenderer, textTexture, nullptr, &destRect);
            }
        }
    }

    // Reset color modulation for the actual text
    SDL_SetTextureColorMod(textTexture, fg.r, fg.g, fg.b);
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopy(this->textureRenderer, textTexture, nullptr, &destRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void TextureManager::drawBorderedText(std::string_view text, int x, int y, int pt, SDL_Color fg, SDL_Color bg,
                                      TTF_Font *font) {
    SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, text.data(), fg);
    if (textSurface == nullptr) {
        std::clog << "Error loading surface: " << SDL_GetError() << '\n';
        SDL_ClearError();
        std::terminate();
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(this->textureRenderer, textSurface);
    if (textTexture == nullptr) {
        std::clog << "Error loading texture: " << SDL_GetError() << '\n';
        SDL_ClearError();

        SDL_FreeSurface(textSurface);
        std::terminate();
    }

    // Render text with outline by rendering text multiple times with slight offsets
    SDL_Rect destRect(x, y, textSurface->w, textSurface->h);

    // Draw the outline first
    SDL_SetTextureColorMod(textTexture, bg.r, bg.g, bg.b);
    for (int i = 1; i <= pt; ++i) {
        for (int dx = -i; dx <= i; ++dx) {
            for (int dy = -i; dy <= i; ++dy) {
                destRect.x = x + dx;
                destRect.y = y + dy;
                SDL_RenderCopy(this->textureRenderer, textTexture, nullptr, &destRect);
            }
        }
    }

    // Reset color modulation for the actual text
    SDL_SetTextureColorMod(textTexture, fg.r, fg.g, fg.b);
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopy(this->textureRenderer, textTexture, nullptr, &destRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

TextureManager::operator bool() const {
    return this->isInitialized;
}
