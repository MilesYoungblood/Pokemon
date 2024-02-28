//
// Created by Miles Youngblood on 2/26/2024.
//

#pragma once

#include "../Button/Button.h"

class Panel : public Rectangle {
private:
    std::vector<std::vector<std::unique_ptr<Button>>> buttons;
    int currentCol{ 0 };
    int currentRow{ 0 };

    int buttonW;
    int buttonH;
    int buttonBorder;

    SDL_Texture *arrow{ TextureManager::getInstance().loadTexture("RightArrowWhite.png") };

    void init(int r, int c);

public:
    Panel(SDL_Rect dest, int borderSize, int numRows, int numCols, int w, int h, int pt);

    Panel(SDL_Rect dest, SDL_Color fg, int borderSize, int numRows, int numCols, int w, int h, int pt);

    Panel(const Panel &) = default;

    Panel(Panel &&) noexcept = default;

    Panel &operator=(const Panel &) = default;

    Panel &operator=(Panel &&) noexcept = default;

    ~Panel() override;

    template<std::size_t row, std::size_t col, typename ...Args>
    void add(Args ...args) {
        const double x_interval = this->getW() / static_cast<double>(this->buttons[0].size());
        const double y_interval = this->getH() / static_cast<double>(this->buttons.size());

        this->buttons[row][col] = std::make_unique<Button>(args...);
        this->buttons[row][col]->setW(this->buttonW);
        this->buttons[row][col]->setH(this->buttonH);

        const int x_pos = this->getX() +
                          static_cast<int>((col * x_interval) + ((x_interval - this->buttons[row][col]->getW()) / 2.0));
        const int y_pos = this->getY() +
                          static_cast<int>((row * y_interval) + ((y_interval - this->buttons[row][col]->getH()) / 2.0));

        this->buttons[row][col]->setX(x_pos);
        this->buttons[row][col]->setY(y_pos);
        this->buttons[row][col]->setBorderSize(this->buttonBorder);
    }

    void update() override;

    void render() const override;
};
