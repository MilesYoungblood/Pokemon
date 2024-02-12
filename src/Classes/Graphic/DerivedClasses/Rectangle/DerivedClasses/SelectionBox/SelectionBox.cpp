//
// Created by Miles Youngblood on 2/3/2024.
//

#include "../../../../../../Classes/Singleton/DerivedClasses/Game/Game.h"
#include "SelectionBox.h"

SelectionBox::SelectionBox(SDL_Rect dest, SDL_Color bg, int borderSize, const std::vector<std::string> &options)
        : Rectangle(dest, bg, borderSize), options(options) {}

SelectionBox::SelectionBox(SDL_Rect dest, SDL_Color fg, SDL_Color bg, int borderSize,
                           const std::vector<std::string> &options)
        : Rectangle(dest, fg, bg, borderSize), options(options) {}

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
    else {
        consecutive = false;
    }
}

void SelectionBox::render() const {
    this->renderBox();

    const int interval = static_cast<int>(this->getDest().h / static_cast<double>(options.size()));

    const int percent = static_cast<int>(this->getDest().w * 0.05);

    for (int i = 0; i < options.size(); ++i) {
        TextureManager::getInstance().draw(
                Texture(options.at(i), Constants::Color::BLACK).getTexture(),
                SDL_Rect(
                        this->getDest().x + percent,
                        this->getDest().y + Game::FONT_SIZE + interval * i,
                        Game::FONT_SIZE * static_cast<int>(options.at(i).length()),
                        Game::FONT_SIZE
                )
        );
    }

    TextureManager::getInstance().draw(
            Texture("RightArrow.png").getTexture(),
            SDL_Rect(
                    this->getDest().w - percent + Game::FONT_SIZE,
                    this->getDest().y + Game::FONT_SIZE + interval * this->current,
                    Game::FONT_SIZE,
                    Game::FONT_SIZE
            )
    );
}
