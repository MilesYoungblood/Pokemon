//
// Created by Miles Youngblood on 2/22/2024.
//

#include "Button.h"

Button::Button(SDL_Rect dest, SDL_Color fg, int borderSize, std::string label, const std::function<void()> &f)
        : Rectangle(dest, fg, borderSize), text(std::move(label)), onPress(f) {}

Button::Button(SDL_Color fg, std::string label, const std::function<void()> &f)
        : Rectangle(SDL_Rect(), fg, 0), text(std::move(label)), onPress(f) {}

void Button::press() {
    if (this->onPress == nullptr) {
        std::clog << "This button \"" << this->text << "\" does nothing\n";
    }
    else {
        this->onPress();
    }
}

void Button::update() {
}

void Button::render() const {
    this->renderBox();

    int width;
    int height;
    TTF_SizeUTF8(TextureManager::getInstance().getFont(), this->text.c_str(), &width, &height);
    TextureManager::getInstance().drawBorderedText(
            this->text,
            this->getDest().x + this->getDest().w / 2 - width / 2,
            this->getDest().y + this->getDest().h / 2 - height / 2,
            2,
            Constants::Color::WHITE,
            Constants::Color::BLACK
    );
}
