//
// Created by Miles Youngblood on 12/5/2023.
//

#pragma once

#include "../../Rectangle.h"

class TextBox : public Rectangle {
private:
    std::size_t lettersPrinted{ 0 };
    std::queue<std::string> messageQueue;
    std::queue<std::function<void()>> functionQueue;

    SDL_Rect textBox;
    SDL_Texture *text{ nullptr };

public:
    TextBox(SDL_Rect dest, int borderSize, int x, int y);

    TextBox(const TextBox &) = default;

    TextBox(TextBox &&) noexcept = default;

    TextBox &operator=(const TextBox &) = default;

    TextBox &operator=(TextBox &&) noexcept = default;

    ~TextBox() override;

    void push(const char *message, const std::function<void()> &function = nullptr);

    void push(const std::string &message, const std::function<void()> &function = nullptr);

    void push(const std::vector<const char *> &messages, const std::vector<std::function<void()>> &functions = std::vector<std::function<void()>>());

    void push(const std::vector<std::string> &messages, const std::vector<std::function<void()>> &functions = std::vector<std::function<void()>>());

    void pop();

    void update() override;

    void render() const override;

    [[nodiscard]] bool isPrinting() const;

    [[nodiscard]] bool empty() const;
};
