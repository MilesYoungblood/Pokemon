//
// Created by Miles Youngblood on 12/12/2023.
//

#include "Texture.h"

Texture::Texture(SDL_Rect dest) : Graphic(dest) {}

Texture::Texture(SDL_Texture *txt) : texture(txt) {}

void Texture::setTexture(SDL_Texture *newTexture) {
    this->texture = newTexture;
}

SDL_Texture *Texture::getTexture() const {
    return this->texture;
}

Texture::Texture(const std::string &path, SDL_Rect dest)
        : Graphic(dest), texture(TextureManager::getInstance().loadTexture(path)) {}

Texture::Texture(const std::string &text, SDL_Color fg, SDL_Rect dest)
        : Graphic(dest), texture(TextureManager::getInstance().loadText(text, fg)) {}

Texture::Texture(Texture &&toMove) noexcept : Graphic(toMove.getDest()), texture(toMove.texture) {
    toMove.texture = nullptr;
}

Texture &Texture::operator=(Texture &&rhs) noexcept {
    this->texture = rhs.texture;
    rhs.texture = nullptr;

    return *this;
}

Texture::~Texture() {
    SDL_DestroyTexture(this->texture);
    if (strlen(SDL_GetError()) > 0) {
        std::clog << "Unable to destroy texture: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
}

void Texture::update() {}

void Texture::render() const {
    TextureManager::getInstance().draw(this->texture, this->getDest());
}
