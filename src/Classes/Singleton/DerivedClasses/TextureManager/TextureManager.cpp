//
// Created by Miles on 11/28/2023.
//

#include "TextureManager.h"

namespace {
    bool called = false;
}

TextureManager::~TextureManager() {
    if (not called) {
        std::clog << "TextureManager::clean() not called\n";
    }
}

bool TextureManager::init(SDL_Renderer *renderer) {
    // only allow this function to be called once per instantiation of TextureManager object
    if (not this->isInitialized) {
        this->textureRenderer = renderer;

        this->font = TTF_OpenFont("../assets/fonts/PokemonGb-RAeo.ttf", TextureManager::FONT_SIZE);
        if (this->font == nullptr) {
            std::clog << "Error creating font: " << SDL_GetError() << '\n';
            SDL_ClearError();
            return false;
        }

        this->isInitialized = true;
        return true;
    }
    return false;
}

void TextureManager::clean() {
    TTF_CloseFont(this->font);
    this->textureRenderer = nullptr;
    called = true;
}

SDL_Texture *TextureManager::loadTexture(const std::string &path) {
    return IMG_LoadTexture(this->textureRenderer, std::string_view("../assets/images/" + path).data());
}

std::tuple<SDL_Texture *, Uint32, Uint32> TextureManager::loadTextureData(const std::string &path) {
    SDL_Surface *temp = IMG_Load(std::string_view("../assets/images/" + path).data());
    if (temp == nullptr) {
        throw std::runtime_error("Error creating surface\n");
    }

    int rows = temp->h;
    int cols = temp->w;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);
    SDL_FreeSurface(temp);

    return std::make_tuple(texture, rows, cols);
}

std::tuple<SDL_Texture *, int, int> TextureManager::loadTextData(std::string_view text, SDL_Color fg, int wLength) {
    SDL_Surface *temp = TTF_RenderUTF8_Blended_Wrapped(this->font, text.data(), fg, wLength);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);

    const int w = temp->w;
    const int h = temp->h;

    SDL_FreeSurface(temp);

    return std::make_tuple(texture, w, h);
}

SDL_Texture *TextureManager::loadText(const char *text, SDL_Color fg) {
    SDL_Surface *temp = TTF_RenderText_Solid(this->font, text, fg);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);
    SDL_FreeSurface(temp);

    return texture;
}

SDL_Texture *TextureManager::loadText(std::string_view text, SDL_Color fg) {
    SDL_Surface *temp = TTF_RenderText_Solid(this->font, text.data(), fg);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);
    SDL_FreeSurface(temp);

    return texture;
}

void TextureManager::draw(SDL_Texture *texture, const SDL_Rect &dest) {
    SDL_RenderCopy(this->textureRenderer, texture, nullptr, &dest);
}

void TextureManager::drawFrame(SDL_Texture *texture, const SDL_Rect &dest, int col, int row) {
    const SDL_Rect src{ dest.w * col, dest.h * row, dest.w, dest.h };
    SDL_RenderCopy(this->textureRenderer, texture, &src, &dest);
}

void TextureManager::drawRect(const SDL_Rect &dest, SDL_Color fg, int pt) {
    SDL_Rect border(dest.x - 1, dest.y - 1, dest.w + 2, dest.h + 2);

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

    SDL_Rect border(dest.x - 1, dest.y - 1, dest.w + 2, dest.h + 2);

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

void TextureManager::drawBorderedText(const char *text, int x, int y, int pt, SDL_Color fg, SDL_Color bg) {
    SDL_Surface *textSurface = TTF_RenderUTF8_Solid(this->font, text, fg);
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
    SDL_FreeSurface(textSurface);

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
}

void TextureManager::drawBorderedText(std::string_view text, int x, int y, std::optional<int> maxW, std::optional<int> maxH, int pt, SDL_Color fg, SDL_Color bg) {
    SDL_Surface *textSurface = TTF_RenderUTF8_Solid(this->font, text.data(), fg);
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
    if (maxW.has_value()) {
        destRect.w = std::min(destRect.w, maxW.value());
    }
    if (maxH.has_value()) {
        destRect.h = std::min(destRect.h, maxH.value());
    }

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

TTF_Font *TextureManager::getFont() const {
    return this->font;
}

TextureManager::operator bool() const {
    return this->isInitialized;
}
