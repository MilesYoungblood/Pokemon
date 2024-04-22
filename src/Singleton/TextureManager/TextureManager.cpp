//
// Created by Miles on 11/28/2023.
//

#include "../../Graphic/Texture/Texture.h"
#include "TextureManager.h"

namespace {
    bool called = false;
}

TextureManager::~TextureManager() {
    if (not called) {
        std::clog << "TextureManager::clean() not called\n";
    }
}

TextureManager & TextureManager::getInstance() {
    static TextureManager textureManager;
    return textureManager;
}

bool TextureManager::init(SDL_Renderer *renderer) {
    // only allow this function to be called once per instantiation of TextureManager object
    if (not this->isInitialized) {
        this->textureRenderer = renderer;

        SDL_SetRenderDrawBlendMode(this->textureRenderer, SDL_BLENDMODE_BLEND);

        this->font = TTF_OpenFont("../assets/fonts/PokemonGb-RAeo.ttf", FONT_SIZE);
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

SDL_Texture *TextureManager::loadTexture(const std::string &path) const {
    return IMG_LoadTexture(this->textureRenderer, std::string_view("../assets/images/" + path).data());
}

std::tuple<SDL_Texture *, Uint32, Uint32> TextureManager::loadTextureData(const std::string &path) const {
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

std::tuple<SDL_Texture *, int, int> TextureManager::loadTextData(const std::string &text, SDL_Color fg) const {
    SDL_Surface *temp = TTF_RenderUTF8_Solid(this->font, text.data(), fg);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);

    const int w = temp->w;
    const int h = temp->h;

    SDL_FreeSurface(temp);

    return std::make_tuple(texture, w, h);
}

std::tuple<SDL_Texture *, int, int> TextureManager::loadWrappedTextData(const std::string &text, const SDL_Color fg, const int wLength) const {
    SDL_Surface *temp = TTF_RenderUTF8_Blended_Wrapped(this->font, text.data(), fg, wLength);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);

    const int w = temp->w;
    const int h = temp->h;

    SDL_FreeSurface(temp);

    return std::make_tuple(texture, w, h);
}

SDL_Texture *TextureManager::loadText(const std::string &text, const SDL_Color fg) const {
    SDL_Surface *temp = TTF_RenderUTF8_Solid(this->font, text.data(), fg);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->textureRenderer, temp);
    SDL_FreeSurface(temp);

    return texture;
}

void TextureManager::draw(SDL_Texture *texture, const SDL_Rect dest) const {
    SDL_RenderCopy(this->textureRenderer, texture, nullptr, &dest);
}

void TextureManager::drawFrame(SDL_Texture *texture, const SDL_Rect dest, const int col, const int row) const {
    const SDL_Rect src(dest.w * col, dest.h * row, dest.w, dest.h);
    SDL_RenderCopy(this->textureRenderer, texture, &src, &dest);
}

void TextureManager::drawRect(const SDL_Rect dest, const SDL_Color fg, const int pt) const {
    SDL_Rect border(dest.x - 1, dest.y - 1, dest.w + 2, dest.h + 2);

    SDL_Color previous;
    // save the previous draw color
    SDL_GetRenderDrawColor(this->textureRenderer, &previous.r, &previous.g, &previous.b, &previous.a);

    SDL_SetRenderDrawColor(this->textureRenderer, fg.r, fg.g, fg.b, fg.a);
    for (int i = 0; i < pt; ++i) {
        SDL_RenderDrawRect(this->textureRenderer, &border);
        --border.x;
        --border.y;
        border.w += 2;
        border.h += 2;
    }

    // reset the draw color to its previous state
    SDL_SetRenderDrawColor(this->textureRenderer, previous.r, previous.g, previous.b, previous.a);
}

void TextureManager::drawRect(const SDL_Rect dest, const SDL_Color fg, const SDL_Color bg, const int pt) const {
    SDL_Color previous;
    // save the previous draw color
    SDL_GetRenderDrawColor(this->textureRenderer, &previous.r, &previous.g, &previous.b, &previous.a);

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

    // reset the draw color to its previous state
    SDL_SetRenderDrawColor(this->textureRenderer, previous.r, previous.g, previous.b, previous.a);
}

void TextureManager::drawBorderedText(const Texture &text, const int pt, const SDL_Color fg, const SDL_Color bg) {
    // Render text with outline by rendering text multiple times with slight offsets
    Texture copy(text);

    // Draw the outline first
    SDL_SetTextureColorMod(static_cast<SDL_Texture *>(copy), bg.r, bg.g, bg.b);
    for (int i = 1; i <= pt; ++i) {
        for (int dx = -i; dx <= i; ++dx) {
            for (int dy = -i; dy <= i; ++dy) {
                copy.setX(copy.getX() + dx);
                copy.setY(copy.getY() + dy);
                copy.render();
            }
        }
    }

    // Reset color modulation for the actual text
    SDL_SetTextureColorMod(static_cast<SDL_Texture *>(copy), fg.r, fg.g, fg.b);
    copy.render();
}

void TextureManager::drawScreen() const {
    SDL_Color previous;
    // save the previous draw color
    SDL_GetRenderDrawColor(this->textureRenderer, &previous.r, &previous.g, &previous.b, &previous.a);

    // draw the black screen at its alpha value
    SDL_SetRenderDrawColor(this->textureRenderer, this->screenColor.r, this->screenColor.g, this->screenColor.b, this->screenColor.a);
    SDL_RenderFillRect(this->textureRenderer, nullptr);

    // reset the draw color to its previous state
    SDL_SetRenderDrawColor(this->textureRenderer, previous.r, previous.g, previous.b, previous.a);
}

void TextureManager::darken() {
    this->screenColor.a = std::min(this->screenColor.a + 2, SDL_ALPHA_OPAQUE);
}

void TextureManager::brighten() {
    this->screenColor.a = std::max(this->screenColor.a - 2, SDL_ALPHA_TRANSPARENT);
}

void TextureManager::setScreenColor(const Uint8 r, const Uint8 g, const Uint8 b) {
    this->screenColor.r = r;
    this->screenColor.g = g;
    this->screenColor.b = b;
}

void TextureManager::setScreenOpacity(const Uint8 alpha) {
    this->screenColor.a = alpha;
}

bool TextureManager::isScreenOpaque() const {
    return this->screenColor.a == SDL_ALPHA_OPAQUE;
}

bool TextureManager::isScreenTransparent() const {
    return this->screenColor.a == SDL_ALPHA_TRANSPARENT;
}

TTF_Font *TextureManager::getFont() const {
    return this->font;
}

TextureManager::operator bool() const {
    return this->isInitialized;
}
