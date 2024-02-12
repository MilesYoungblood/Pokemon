//
// Created by Miles Youngblood on 12/5/2023.
//

#pragma once

#include "../../Rectangle.h"

class TextBox : public Rectangle, public Singleton<TextBox> {
private:
    std::pair<int, int> textPos;

    int textWidth{ 0 };
    int textHeight{ 0 };

    std::size_t lettersPrinted{ 0 };
    std::queue<std::string> messages;

    SDL_Texture *text{ nullptr };

    void (*finishedPrinting)(){ nullptr };

    friend Singleton<TextBox>;

    TextBox() = default;

public:
    TextBox(const TextBox &) = default;

    TextBox(TextBox &&) noexcept = default;

    TextBox &operator=(const TextBox &) = default;

    TextBox &operator=(TextBox &&) noexcept = default;

    ~TextBox() override;

    void init(SDL_Rect newRect, int newBorder, int x, int y);

    void push(const char *message);

    void push(const std::string &message);

    void push(const std::vector<const char *> &toPush);

    void push(const std::vector<std::string> &toPush);

    void pop();

    void update() override;

    void render() const override;

    void setFinishedCallback(void (*instructions)());

    [[nodiscard]] bool isPrinting() const;

    [[nodiscard]] bool empty() const;
};
