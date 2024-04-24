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

    void add(const std::string &label, SDL_Color fg, const std::function<void()> &f);

    void update() override;

    void render() const override;

    void clear();

private:
    Matrix<std::shared_ptr<Button>> buttons;

    int currentRow{ 0 };
    int currentCol{ 0 };

    int colCounter{ 0 };
    int rowCounter{ 0 };

    int buttonWidth;
    int buttonHeight;
    int buttonBorder;

    SDL_Texture *arrow;

    void init();
};
