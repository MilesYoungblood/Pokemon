//
// Created by Miles Youngblood on 12/12/2023.
//

#include "Texture.h"

Texture::Texture(const std::string &path) : texture(TextureManager::getInstance().loadTexture(path)) {}

Texture::Texture(const std::string &text, SDL_Color fg) : texture(TextureManager::getInstance().loadText(text, fg)) {}

Texture::Texture(Texture &&toMove) noexcept : texture(toMove.texture) {
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

void Texture::render() const {}

SDL_Texture *Texture::getTexture() const {
    return this->texture;
}
