//
// Created by Miles Youngblood on 2/6/2024.
//

#include "ResourceBar.h"

ResourceBar::ResourceBar(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize, int amount)
        : Rectangle(dest, fg, bg, borderSize), progress(amount) {}

void ResourceBar::raise(int n) {
    this->progress = std::max(this->progress + n, 100);
}

void ResourceBar::lower(int n) {
    this->progress = std::min(this->progress - n, 0);
}

void ResourceBar::update() {}

void ResourceBar::render() const {
    TextureManager::getInstance().drawRect(this->getDest(), this->getBg(), this->getBorderSize());

    TextureManager::getInstance().drawRect(
            SDL_Rect(
                    this->getDest().x,
                    this->getDest().y,
                    static_cast<int>(this->getDest().w * (this->progress / 100.0)),
                    this->getDest().h
            ),
            this->getFg(),
            this->getBg(),
            0
    );
}

