//
// Created by Miles Youngblood on 2/6/2024.
//

#include "../../../../../Singleton/DerivedClasses/TextureManager/TextureManager.h"
#include "ResourceBar.h"

ResourceBar::ResourceBar(const SDL_Rect dest, const SDL_Color fg, const int borderSize, const int amount)
        : Rectangle(dest, fg, borderSize), progress(amount, 100) {}

Component::Resource &ResourceBar::getProgress() {
    return this->progress;
}

void ResourceBar::update() {}

void ResourceBar::render() const {
    TextureManager::getInstance().drawRect(this->getDest(), this->getBg(), this->getBorderSize());

    TextureManager::getInstance().drawRect(
            SDL_Rect(
                    this->getDest().x,
                    this->getDest().y,
                    static_cast<int>(this->getDest().w * (this->progress.getCurrent() / 100.0)),
                    this->getDest().h
            ),
            this->getFg(),
            this->getBg(),
            0
    );
}
