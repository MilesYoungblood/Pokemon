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
    const auto data = TextureManager::getInstance().loadTextData(label, this->getFg());

    const int w = std::min(std::get<1>(data), this->getW());
    const int h = std::min(std::get<2>(data), this->getH());

    const SDL_Rect textDest(
        this->getX() + this->getW() / 2 - w / 2,
        this->getY() + this->getH() / 2 - h / 2,
        w,
        h
    );

    this->text = Texture(std::get<0>(data), textDest);
}

void Button::press() const {
    if (this->onPress != nullptr) {
        this->onPress();
    }
}

void Button::render() const {
    Rectangle::render();

    TextureManager::drawBorderedText(
            this->text,
            2,
            Constants::Color::WHITE,
            Constants::Color::BLACK
    );
}
