//
// Created by Miles Youngblood on 2/3/2024.
//

#include "../../../Singleton/Game/Game.h"
#include "../../../Singleton/KeyManager/KeyManager.h"
#include "../../Texture/Texture.h"
#include "SelectionBox.h"

SelectionBox::SelectionBox(const SDL_Rect dest, const int borderSize,
                           const std::vector<std::pair<std::string, std::function<void()>>> &options)
        : Rectangle(dest, borderSize), options(options) {}

SelectionBox::SelectionBox(const SDL_Rect dest, const SDL_Color fg, const int borderSize,
                           const std::vector<std::pair<std::string, std::function<void()>>> &options)
        : Rectangle(dest, fg, borderSize), options(options) {}

SelectionBox::SelectionBox(const SDL_Rect dest, const SDL_Color fg, const SDL_Color bg, const int borderSize,
                           const std::vector<std::pair<std::string, std::function<void()>>> &options)
        : Rectangle(dest, fg, bg, borderSize), options(options) {}

void SelectionBox::update() {
    static bool consecutive = false;

    if (KeyManager::getInstance().getKey(SDL_SCANCODE_W)) {
        if (not consecutive) {
            this->current = std::max(0, this->current - 1);
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_S)) {
        if (not consecutive) {
            this->current = std::min(static_cast<int>(this->options.size() - 1), this->current + 1);
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_RETURN)) {
        if (not consecutive) {
            if (this->options[this->current].second != nullptr) {
                this->options[this->current].second();
            }
            else {
                std::clog << "This option doesn't do anything\n";
            }
            consecutive = true;
        }
    }
    else {
        consecutive = false;
    }
}

void SelectionBox::render() const {
    this->renderBox();

    const int interval = static_cast<int>(this->getDest().h / static_cast<double>(options.size()));
    const int percent = static_cast<int>(this->getDest().w * 0.05);

    for (int i = 0; i < options.size(); ++i) {
        Texture text(
                options.at(i).first,
                Constants::Color::BLACK,
                SDL_Rect(
                        this->getDest().x + percent,
                        this->getDest().y + Game::FONT_SIZE + interval * i,
                        Game::FONT_SIZE * static_cast<int>(options.at(i).first.length()),
                        Game::FONT_SIZE
                )
        );
        text.render();
    }

    const Texture arrow(
            "RightArrow.png",
            SDL_Rect(
                    this->getDest().w - percent + Game::FONT_SIZE,
                    this->getDest().y + Game::FONT_SIZE + interval * this->current,
                    Game::FONT_SIZE,
                    Game::FONT_SIZE
            )
    );
    arrow.render();
}
