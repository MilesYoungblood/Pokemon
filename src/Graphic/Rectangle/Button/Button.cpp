//
// Created by Miles Youngblood on 2/22/2024.
//

#include "../../../Singleton/TextureManager/TextureManager.h"
#include "Button.h"

Button::Button(const SDL_Rect dest, const SDL_Color fg, const int borderSize, std::string label, const std::function<void()> &f)
        : Rectangle(dest, fg, borderSize), text(std::move(label)), onPress(f) {}

Button::Button(const SDL_Color fg, std::string label, const std::function<void()> &f)
        : Rectangle(SDL_Rect(), fg, 0), text(std::move(label)), onPress(f) {}

void Button::press() const {
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

    width = std::min(width, this->getW());
    height = std::min(height, this->getH());
    TextureManager::getInstance().drawBorderedText(
            this->text,
            this->getX() + this->getW() / 2 - width / 2,
            this->getY() + this->getH() / 2 - height / 2,
            std::make_optional<int>(this->getW()),
            std::make_optional<int>(this->getH()),
            2,
            Constants::Color::WHITE,
            Constants::Color::BLACK
    );
}
