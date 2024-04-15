//
// Created by Miles Youngblood on 2/26/2024.
//

#include "../../../../../Singleton/DerivedClasses/TextureManager/TextureManager.h"
#include "../../../../../Singleton/DerivedClasses/KeyManager/KeyManager.h"
#include "Panel.h"

void Panel::init(const int r, const int c) {
    this->buttons.resize(r);
    for (auto &set : this->buttons) {
        set.resize(c);
        for (auto &button : set) {
            button = nullptr;
        }
    }
}

Panel::Panel(const SDL_Rect dest, const int borderSize, const int numRows, const int numCols, const int w, const int h,  const int pt)
        : Rectangle(dest, borderSize), buttonWeight(w), buttonHeight(h), buttonBorder(pt) {
    this->init(numRows, numCols);
}

Panel::Panel(const SDL_Rect dest, const SDL_Color fg, const int borderSize, const int numRows, const int numCols, const int w, const int h, const int pt)
        : Rectangle(dest, fg, borderSize), buttonWeight(w), buttonHeight(h), buttonBorder(pt) {
    this->init(numRows, numCols);
}

Panel::~Panel() {
    if (this->arrow != nullptr) {
        SDL_DestroyTexture(this->arrow);
        if (strlen(SDL_GetError()) > 0) {
            std::clog << "Unable to destroy arrow: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }
}

void Panel::clear() {
    for (auto &row : this->buttons) {
        for (auto &button : row) {
            button.reset(nullptr);
        }
    }
    this->rowCounter = 0;
    this->colCounter = 0;
}

void Panel::update() {
    static bool consecutive = false;

    if (KeyManager::getInstance().getKey(SDL_SCANCODE_W)) {
        if (not consecutive) {
            if (const int value = std::max(0, this->currentRow - 1); this->buttons[value][currentCol] != nullptr) {
                this->currentRow = value;
                consecutive = true;
            }
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_A)) {
        if (not consecutive) {
            if (const int value = std::max(0, this->currentCol - 1); this->buttons[this->currentRow][value] != nullptr) {
                this->currentCol = value;
                consecutive = true;
            }
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_S)) {
        if (not consecutive) {
            if (const int value = std::min(this->currentRow + 1, static_cast<int>(this->buttons.size()) - 1); this->buttons[value][this->currentCol] != nullptr) {
                this->currentRow = value;
                consecutive = true;
            }
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_D)) {
        if (not consecutive) {
            if (const int value = std::min(this->currentCol + 1, static_cast<int>(this->buttons[0].size()) - 1); this->buttons[this->currentRow][value] != nullptr) {
                this->currentCol = value;
                consecutive = true;
            }
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_RETURN)) {
        if (not consecutive) {
            if (this->buttons[this->currentRow][this->currentCol] != nullptr) {
                this->buttons[this->currentRow][this->currentCol]->press();
                consecutive = true;
            }
        }
    }
    else {
        consecutive = false;
    }
}

void Panel::render() const {
    this->renderBox();
    for (std::size_t row = 0; row < this->buttons.size(); ++row) {
        for (std::size_t col = 0; col < this->buttons[row].size(); ++col) {
            if (this->buttons.at(row).at(col) != nullptr) {
                this->buttons.at(row).at(col)->render();

                if (row == this->currentRow and col == this->currentCol) {
                    const double xInterval = this->getW() / static_cast<double>(this->buttons[0].size());
                    const double yInterval = this->getH() / static_cast<double>(this->buttons.size());

                    const int xPos = this->getX() + static_cast<int>(this->currentCol * xInterval + (xInterval - this->buttons[this->currentRow][this->currentCol]->getW()) / 2.0) - this->buttonHeight;
                    const int yPos = this->getY() + static_cast<int>(this->currentRow * yInterval + (yInterval - this->buttons[this->currentRow][this->currentCol]->getH()) / 2.0);

                    TextureManager::getInstance().draw(
                            this->arrow,
                            SDL_Rect(
                                    xPos,
                                    yPos,
                                    this->buttonHeight,
                                    this->buttonHeight
                            )
                    );
                }
            }
        }
    }
}
