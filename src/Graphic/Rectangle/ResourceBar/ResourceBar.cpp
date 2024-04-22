//
// Created by Miles Youngblood on 2/6/2024.
//

#include "ResourceBar.h"

ResourceBar::ResourceBar(const SDL_Rect dest, const SDL_Color fg, const int borderSize, const int amount)
        : Rectangle(dest, fg, borderSize), progress(amount, 100) {
    const SDL_Rect rect(dest.x, dest.y, static_cast<int>(dest.w * (this->progress.getCurrent() / 100.0)), dest.h);
    this->progressRect = Rectangle(rect, fg, this->getBg(), 0);
}

Component::Resource &ResourceBar::getProgress() {
    return this->progress;
}

void ResourceBar::update() {
    this->progressRect.setW(static_cast<int>(this->getDest().w * (this->progress.getCurrent() / 100.0)));
}

void ResourceBar::render() const {
    Rectangle::render();
    this->progressRect.render();
}
