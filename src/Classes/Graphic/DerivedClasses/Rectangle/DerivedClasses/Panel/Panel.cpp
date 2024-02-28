//
// Created by Miles Youngblood on 2/26/2024.
//

#include "../../../../../Singleton/DerivedClasses/Game/Game.h"
#include "Panel.h"

void Panel::init(int r, int c) {
    this->buttons.resize(r);
    for (auto &row : this->buttons) {
        row.resize(c);
        for (auto &button : row) {
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
            this->currentRow = std::max(0, this->currentRow - 1);
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_A)) {
        if (not consecutive) {
            this->currentCol = std::max(0, this->currentCol - 1);
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_S)) {
        if (not consecutive) {
            this->currentRow = std::min(this->currentRow + 1, static_cast<int>(this->buttons.size()) - 1);
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_D)) {
        if (not consecutive) {
            this->currentCol = std::min(this->currentCol + 1, static_cast<int>(this->buttons.size()) - 1);
            consecutive = true;
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_Scancode::SDL_SCANCODE_RETURN)) {
        if (not consecutive) {
            this->buttons[this->currentCol][this->currentRow]->click();
            consecutive = true;
        }
    }
    else {
        consecutive = false;
    }
}

void Panel::render() const {
    this->renderBox();
    for (const auto &row : this->buttons) {
        for (const auto &button : row) {
            button->render();
        }
    }

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
