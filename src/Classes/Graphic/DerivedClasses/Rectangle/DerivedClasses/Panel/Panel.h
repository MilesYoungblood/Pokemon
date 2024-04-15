//
// Created by Miles Youngblood on 2/26/2024.
//

#pragma once

#include "../Button/Button.h"

class Panel final : public Rectangle {
public:
    Panel(SDL_Rect dest, int borderSize, int numRows, int numCols, int w, int h, int pt);

    Panel(SDL_Rect dest, SDL_Color fg, int borderSize, int numRows, int numCols, int w, int h, int pt);

    Panel(const Panel &) = default;

    Panel(Panel &&) noexcept = default;

    Panel &operator=(const Panel &) = default;

    Panel &operator=(Panel &&) noexcept = default;

    ~Panel() override;

    template<typename ...Args>
    void add(Args ...args) {
        if (this->rowCounter == this->buttons.size()) {
            return;
        }
        const double xInterval = this->getW() / static_cast<double>(this->buttons[0].size());
        const double yInterval = this->getH() / static_cast<double>(this->buttons.size());

        this->buttons[this->rowCounter][this->colCounter] = std::make_unique<Button>(args...);
        this->buttons[this->rowCounter][this->colCounter]->setW(this->buttonWeight);
        this->buttons[this->rowCounter][this->colCounter]->setH(this->buttonHeight);

        const int xPos = this->getX() +
                          static_cast<int>(this->colCounter * xInterval + (xInterval - this->buttons[this->rowCounter][this->colCounter]->getW()) / 2.0);
        const int yPos = this->getY() +
                          static_cast<int>(this->rowCounter * yInterval + (yInterval - this->buttons[this->rowCounter][this->colCounter]->getH()) / 2.0);

        this->buttons[this->rowCounter][this->colCounter]->setX(xPos);
        this->buttons[this->rowCounter][this->colCounter]->setY(yPos);
        this->buttons[this->rowCounter][this->colCounter]->setBorderSize(this->buttonBorder);

        ++this->colCounter;
        if (this->colCounter == this->buttons[this->rowCounter].size()) {
            ++this->rowCounter;
            this->colCounter = 0;
        }
    }

    void clear();

    void update() override;

    void render() const override;

private:
    std::vector<std::vector<std::unique_ptr<Button>>> buttons;
    int currentRow{ 0 };
    int currentCol{ 0 };

    int colCounter{ 0 };
    int rowCounter{ 0 };

    int buttonWeight;
    int buttonHeight;
    int buttonBorder;

    SDL_Texture *arrow{ TextureManager::getInstance().loadTexture("RightArrowWhite.png") };

    void init(int r, int c);
};
