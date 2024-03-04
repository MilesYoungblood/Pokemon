//
// Created by Miles Youngblood on 2/26/2024.
//

#include "../../../../../Singleton/DerivedClasses/Game/Game.h"
#include "Panel.h"

void Panel::init(int r, int c) {
    this->buttons.resize(r);
    for (auto &set : this->buttons) {
        set.resize(c);
        for (auto &button : set) {
            button = nullptr;
        }
    }
}

Panel::Panel(SDL_Rect dest, int borderSize, int numRows, int numCols, int w, int h, int pt)
        : Rectangle(dest, borderSize), buttonW(w), buttonH(h), buttonBorder(pt) {
    this->init(numRows, numCols);
}

Panel::Panel(SDL_Rect dest, SDL_Color fg, int borderSize, int numRows, int numCols, int w, int h, int pt)
        : Rectangle(dest, fg, borderSize), buttonW(w), buttonH(h), buttonBorder(pt) {
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

void Panel::update() {
    static bool consecutive = false;

    if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_W)) {
        if (not consecutive) {
            const int value = std::max(0, this->currentRow - 1);
            if (this->buttons[value][currentCol] != nullptr) {
                this->currentRow = value;
                consecutive = true;
            }
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A)) {
        if (not consecutive) {
            const int value = std::max(0, this->currentCol - 1);
            if (this->buttons[this->currentRow][value] != nullptr) {
                this->currentCol = value;
                consecutive = true;
            }
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S)) {
        if (not consecutive) {
            const int value = std::min(this->currentRow + 1, static_cast<int>(this->buttons.size()));
            if (this->buttons[value][this->currentCol] != nullptr) {
                this->currentRow = value;
                consecutive = true;
            }
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D)) {
        if (not consecutive) {
            const int value = std::min(this->currentCol + 1, static_cast<int>(this->buttons.size()) - 1);
            if (this->buttons[this->currentRow][value] != nullptr) {
                this->currentCol = value;
                consecutive = true;
            }
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN)) {
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
                    const double x_interval = this->getW() / static_cast<double>(this->buttons[0].size());
                    const double y_interval = this->getH() / static_cast<double>(this->buttons.size());

                    const int x_pos = this->getX() + static_cast<int>((this->currentCol * x_interval) + ((x_interval - this->buttons[this->currentCol][this->currentRow]->getW()) / 2.0)) - this->buttonH;
                    const int y_pos = this->getY() + static_cast<int>((this->currentRow * y_interval) + ((y_interval - this->buttons[this->currentCol][this->currentRow]->getH()) / 2.0));

                    TextureManager::getInstance().draw(
                            this->arrow,
                            SDL_Rect(
                                    x_pos,
                                    y_pos,
                                    this->buttonH,
                                    this->buttonH
                            )
                    );
                }
            }
        }
    }
}
