//
// Created by Miles Youngblood on 2/3/2024.
//

#include "../../../Singleton/Game/Game.h"
#include "../../../Singleton/KeyManager/KeyManager.h"
#include "SelectionBox.h"

// TODO recalculate maxVisible

SelectionBox::SelectionBox(const SDL_Rect dest, const int borderSize,
                           const std::vector<std::pair<std::string, std::function<void()>>> &options)
        : Rectangle(dest, borderSize), maxVisible(6), options(options) {
    const int interval = static_cast<int>(this->getDest().h / static_cast<double>(options.size()));
    const int percent = static_cast<int>(this->getDest().w * 0.05);

    this->arrow = Texture(
        "RightArrow.png",
        SDL_Rect(
                this->getDest().w - percent + Game::FONT_SIZE,
                this->getDest().y + Game::FONT_SIZE + interval * this->current,
                Game::FONT_SIZE,
                Game::FONT_SIZE
        )
    );
}

void SelectionBox::update() {
    static bool consecutive = false;

    if (KeyManager::getInstance().getKey(SDL_SCANCODE_W)) {
        if (not consecutive) {
            this->current = (this->current - 1 + static_cast<int>(this->options.size())) % static_cast<int>(this->options.size());
            if (this->current == this->options.size() - 1) {
                this->topVisible = std::max(0, static_cast<int>(this->options.size()) - this->maxVisible);
            }
            else if (this->current < this->topVisible) {
                this->topVisible = std::max(0, this->current);
            }
            this->updateArrow();
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_S)) {
        if (not consecutive) {
            this->current = (this->current + 1) % static_cast<int>(this->options.size());
            if (this->current == 0) {
                this->topVisible = 0;
            }
            else if (this->current >= this->topVisible + this->maxVisible) {
                this->topVisible = std::min(this->current - this->topVisible + 1, static_cast<int>(this->options.size()) - this->maxVisible);
            }
            this->updateArrow();
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_RETURN)) {
        if (not consecutive) {
            if (this->options[this->current].second != nullptr) {
                this->options[this->current].second();
            }
            else {
                std::clog << this->options[this->current].first << " doesn't do anything\n";
            }
            consecutive = true;
        }
    }
    else {
        consecutive = false;
    }
}

void SelectionBox::render() const {
    Rectangle::render();

    const int startY = this->getY() + Game::FONT_SIZE;
    const int interval = static_cast<int>(this->getH() / static_cast<double>(this->maxVisible));
    const int percent = static_cast<int>(this->getW() * 0.05);

    for (int i = 0; i < this->maxVisible; ++i) {
        const int optionIndex = i + this->topVisible;
        if (optionIndex >= this->options.size()) {
            break;
        }

        Texture text(
                this->options.at(optionIndex).first,
                Constants::Color::BLACK,
                SDL_Rect(
                        this->getDest().x + percent,
                        startY + interval * i,
                        Game::FONT_SIZE * static_cast<int>(this->options.at(optionIndex).first.length()),
                        Game::FONT_SIZE
                )
        );
        text.render();
    }

    this->arrow.render();
}

void SelectionBox::updateArrow() {
    const int startY = this->getY() + Game::FONT_SIZE;
    const int interval = static_cast<int>(this->getH() / static_cast<double>(this->maxVisible));
    this->arrow.setY(startY + interval * (this->current - this->topVisible));
}
