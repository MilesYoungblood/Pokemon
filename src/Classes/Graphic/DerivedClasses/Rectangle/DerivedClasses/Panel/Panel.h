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

public:
    Panel(SDL_Rect dest, int borderSize, int numRows, int numCols);

    Panel(SDL_Rect dest, SDL_Color fg, int borderSize, int numRows, int numCols);

    Panel(const Panel &) = default;

    Panel(Panel &&) noexcept = default;

    Panel &operator=(const Panel &) = default;

    Panel &operator=(Panel &&) noexcept = default;

    ~Panel() override = default;

    template<std::size_t row, std::size_t col, typename ...Args>
    void add(Args ...args) {
        this->buttons[row][col] = std::make_unique<Button>(args...);
    }

    void update() override;

    void render() const override;
};

inline void foo() {
    Panel p(SDL_Rect(), 5, 2, 2);
    p.add<0, 0>(
            SDL_Rect(),
            Constants::Color::GREEN,
            5,
            "Pokemon",
            nullptr
    );
}
