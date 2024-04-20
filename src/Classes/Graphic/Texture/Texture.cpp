//
// Created by Miles Youngblood on 12/12/2023.
//

#include "../../Singleton/TextureManager/TextureManager.h"
#include "Texture.h"

Texture::Texture(const std::string &path, const SDL_Rect dest)
        : Graphic(dest), texture(TextureManager::getInstance().loadTexture(path)) {}

Texture::Texture(const std::string &text, const SDL_Color fg, const SDL_Rect dest)
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
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
        if (strlen(SDL_GetError()) > 0) {
            std::clog << "Unable to destroy texture: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }
}

void Texture::update() {}

void Texture::render() const {
    TextureManager::getInstance().draw(this->texture, this->getDest());
}

Texture::Texture(const SDL_Rect dest) : Graphic(dest), texture(nullptr) {}

Texture::Texture(const SDL_Rect dest, SDL_Texture *txt) : Graphic(dest), texture(txt) {}

void Texture::setTexture(SDL_Texture *newTexture) {
    this->texture = newTexture;
}

SDL_Texture *Texture::getTexture() const {
    return this->texture;
}
