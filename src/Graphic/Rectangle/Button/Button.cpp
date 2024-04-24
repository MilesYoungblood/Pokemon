//
// Created by Miles Youngblood on 2/22/2024.
//

#include "../../../Singleton/TextureManager/TextureManager.h"
#include "Button.h"

Button::Button(const SDL_Rect dest, const SDL_Color fg, const int borderSize, const std::string &label, const std::function<void()> &f)
        : Rectangle(dest, fg, borderSize), onPress(f) {
    this->init(label);
}

Button::Button(const SDL_Color fg, const int borderSize, const std::function<void()> &f)
        : Rectangle(SDL_Rect(), fg, borderSize), onPress(f) {}

void Button::init(const std::string &label) {
    SDL_Texture *texture = TextureManager::getInstance().loadText(label, Constants::Color::WHITE);
    int w;
    int h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    w = std::min(w, this->getW());
    h = std::min(h, this->getH());

    const SDL_Rect textDest(
        this->getX() + this->getW() / 2 - w / 2,
        this->getY() + this->getH() / 2 - h / 2,
        w,
        h
    );

    this->text = Texture(texture, textDest);
}

void Button::press() const {
    if (this->onPress != nullptr) {
        this->onPress();
    }
}

void Button::render() const {
    Rectangle::render();
    TextureManager::getInstance().drawBorderedText(
            this->text,
            2,
            Constants::Color::WHITE,
            Constants::Color::BLACK
    );
}
