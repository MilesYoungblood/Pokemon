//
// Created by Miles Youngblood on 2/3/2024.
//

#include "../../../../../../Classes/Singleton/DerivedClasses/Game/Game.h"
#include "SelectionBox.h"

SelectionBox::SelectionBox(SDL_Rect dest, SDL_Color fg, int borderSize, const std::vector<std::string> &options)
        : Rectangle(dest, fg, borderSize), options(options), functions(options.size(), nullptr) {}

SelectionBox::SelectionBox(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize,
                           const std::vector<std::string> &options)
        : Rectangle(dest, fg, bg, borderSize), options(options), functions(options.size(), nullptr) {}

void SelectionBox::update() {
    static bool consecutive = false;

    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W)) {
        if (not consecutive) {
            this->current = std::max(0, this->current - 1);
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S)) {
        if (not consecutive) {
            this->current = std::min(static_cast<int>(this->options.size() - 1), this->current + 1);
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN)) {
        if (not consecutive) {
            if (this->functions[this->current] != nullptr) {
                this->functions[this->current]();
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
                options.at(i),
                Constants::Color::BLACK,
                SDL_Rect(
                        this->getDest().x + percent,
                        this->getDest().y + Game::FONT_SIZE + interval * i,
                        Game::FONT_SIZE * static_cast<int>(options.at(i).length()),
                        Game::FONT_SIZE
                )
        );
        text.render();
    }

    Texture arrow(
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
