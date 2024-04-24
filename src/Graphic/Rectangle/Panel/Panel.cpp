//
// Created by Miles Youngblood on 2/26/2024.
//

#include "../../../Singleton/TextureManager/TextureManager.h"
#include "../../../Singleton/KeyManager/KeyManager.h"
#include "Panel.h"

Panel::Panel(const SDL_Rect dest, const int borderSize, const int numRows, const int numCols, const int w, const int h,  const int pt)
        : Rectangle(dest, borderSize), buttons(numRows, numCols), buttonWidth(w), buttonHeight(h), buttonBorder(pt),
          arrow(TextureManager::getInstance().loadTexture("RightArrowWhite.png")) {
    this->init();
}

Panel::Panel(const SDL_Rect dest, const SDL_Color fg, const int borderSize, const int numRows, const int numCols, const int w, const int h, const int pt)
        : Rectangle(dest, fg, borderSize), buttons(numRows, numCols), buttonWidth(w), buttonHeight(h), buttonBorder(pt),
          arrow(TextureManager::getInstance().loadTexture("RightArrowWhite.png")) {
    this->init();
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

void Panel::add(const std::string &label, SDL_Color fg, const std::function<void()> &f) {
    if (this->rowCounter == this->buttons.getM()) {
        return;
    }
    const double xInterval = this->getW() / static_cast<double>(this->buttons.getN());
    const double yInterval = this->getH() / static_cast<double>(this->buttons.getM());

    this->buttons(this->rowCounter, this->colCounter) = std::make_unique<Button>(fg, this->buttonBorder, f);
    this->buttons(this->rowCounter, this->colCounter)->setW(this->buttonWidth);
    this->buttons(this->rowCounter, this->colCounter)->setH(this->buttonHeight);

    const int xPos = this->getX() +
                     static_cast<int>(this->colCounter * xInterval + (xInterval - this->buttons(this->rowCounter, this->colCounter)->getW()) / 2.0);
    const int yPos = this->getY() +
                     static_cast<int>(this->rowCounter * yInterval + (yInterval - this->buttons(this->rowCounter, this->colCounter)->getH()) / 2.0);

    this->buttons(this->rowCounter, this->colCounter)->setX(xPos);
    this->buttons(this->rowCounter, this->colCounter)->setY(yPos);
    this->buttons(this->rowCounter, this->colCounter)->setBorderSize(this->buttonBorder);

    this->buttons(this->rowCounter, this->colCounter)->init(label);

    ++this->colCounter;
    if (this->colCounter == this->buttons.getN()) {
        ++this->rowCounter;
        this->colCounter = 0;
    }
}

void Panel::update() {
    static bool consecutive = false;

    if (KeyManager::getInstance().getKey(SDL_SCANCODE_W)) {
        if (not consecutive) {
            if (const int value = std::max(0, this->currentRow - 1); this->buttons(value, currentCol) != nullptr) {
                this->currentRow = value;
                consecutive = true;
            }
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_A)) {
        if (not consecutive) {
            if (const int value = std::max(0, this->currentCol - 1); this->buttons(this->currentRow, value) != nullptr) {
                this->currentCol = value;
                consecutive = true;
            }
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_S)) {
        if (not consecutive) {
            if (const int value = std::min(this->currentRow + 1, static_cast<int>(this->buttons.getM()) - 1); this->buttons(value, this->currentCol) != nullptr) {
                this->currentRow = value;
                consecutive = true;
            }
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_D)) {
        if (not consecutive) {
            if (const int value = std::min(this->currentCol + 1, static_cast<int>(this->buttons.getN()) - 1); this->buttons(this->currentRow, value) != nullptr) {
                this->currentCol = value;
                consecutive = true;
            }
        }
    }
    else if (KeyManager::getInstance().getKey(SDL_SCANCODE_RETURN)) {
        if (not consecutive) {
            if (this->buttons(this->currentRow, this->currentCol) != nullptr) {
                this->buttons(this->currentRow, this->currentCol)->press();
                consecutive = true;
            }
        }
    }
    else {
        consecutive = false;
    }
}

void Panel::render() const {
    Rectangle::render();
    for (std::size_t row = 0; row < this->buttons.getM(); ++row) {
        for (std::size_t col = 0; col < this->buttons.getN(); ++col) {
            if (this->buttons(row, col) != nullptr) {
                this->buttons(row, col)->render();

                if (row == this->currentRow and col == this->currentCol) {
                    const double xInterval = this->getW() / static_cast<double>(this->buttons.getN());
                    const double yInterval = this->getH() / static_cast<double>(this->buttons.getM());

                    const int xPos = this->getX() + static_cast<int>(this->currentCol * xInterval + (xInterval - this->buttons(this->currentRow, this->currentCol)->getW()) / 2.0) - this->buttonHeight;
                    const int yPos = this->getY() + static_cast<int>(this->currentRow * yInterval + (yInterval - this->buttons(this->currentRow, this->currentCol)->getH()) / 2.0);

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

void Panel::clear() {
    for (auto &row : this->buttons) {
        for (auto &button : row) {
            button.reset();
        }
    }
    this->rowCounter = 0;
    this->colCounter = 0;
}

void Panel::init() {
    for (auto &set : this->buttons) {
        for (auto &button : set) {
            button = nullptr;
        }
    }
}
