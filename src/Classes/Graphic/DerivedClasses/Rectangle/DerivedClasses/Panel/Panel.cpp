//
// Created by Miles Youngblood on 2/26/2024.
//

#include "../../../../../Singleton/DerivedClasses/KeyManager/KeyManager.h"
#include "Panel.h"

Panel::Panel(SDL_Rect dest, int borderSize, int numRows, int numCols) : Rectangle(dest, borderSize) {
    this->buttons.resize(numRows);
    for (auto &row : this->buttons) {
        row.resize(numCols);
        for (auto &button : row) {
            button = nullptr;
        }
    }
}

Panel::Panel(SDL_Rect dest, SDL_Color fg, int borderSize, int numRows, int numCols) : Rectangle(dest, fg, borderSize) {
    this->buttons.resize(numRows);
    for (auto &row : this->buttons) {
        row.resize(numCols);
        for (auto &button : row) {
            button = nullptr;
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
    for (const auto &set : this->buttons) {
        for (const auto &button : set) {
            button->render();
        }
    }
}
