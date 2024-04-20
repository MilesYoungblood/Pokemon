//
// Created by Miles Youngblood on 2/26/2024.
//

#pragma once

#include "../../../../utility/Matrix/Matrix.h"
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
        if (this->rowCounter == this->buttons.getM()) {
            return;
        }
        const double xInterval = this->getW() / static_cast<double>(this->buttons.getN());
        const double yInterval = this->getH() / static_cast<double>(this->buttons.getM());

        this->buttons(this->rowCounter, this->colCounter) = std::make_optional<Button>(args...);
        this->buttons(this->rowCounter, this->colCounter)->setW(this->buttonWeight);
        this->buttons(this->rowCounter, this->colCounter)->setH(this->buttonHeight);

        const int xPos = this->getX() +
                          static_cast<int>(this->colCounter * xInterval + (xInterval - this->buttons(this->rowCounter, this->colCounter)->getW()) / 2.0);
        const int yPos = this->getY() +
                          static_cast<int>(this->rowCounter * yInterval + (yInterval - this->buttons(this->rowCounter, this->colCounter)->getH()) / 2.0);

        this->buttons(this->rowCounter, this->colCounter)->setX(xPos);
        this->buttons(this->rowCounter, this->colCounter)->setY(yPos);
        this->buttons(this->rowCounter, this->colCounter)->setBorderSize(this->buttonBorder);

        ++this->colCounter;
        if (this->colCounter == this->buttons.getN()) {
            ++this->rowCounter;
            this->colCounter = 0;
        }
    }

    void update() override;

    void render() const override;

    void clear();

private:
    Matrix<std::optional<Button>> buttons;

    int currentRow{ 0 };
    int currentCol{ 0 };

    int colCounter{ 0 };
    int rowCounter{ 0 };

    int buttonWeight;
    int buttonHeight;
    int buttonBorder;

    SDL_Texture *arrow;

    void init();
};
