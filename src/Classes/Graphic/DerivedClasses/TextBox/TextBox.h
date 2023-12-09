//
// Created by Miles Youngblood on 12/5/2023.
//

#pragma once

#include "../../Graphic.h"

class TextBox : public Graphic {
private:
    SDL_Rect rect{ 0, 0, 0, 0 };

    std::pair<int, int> textPos;
    int border{ 1 };

    int textWidth;
    int textHeight;

    std::size_t lettersPrinted{ 0ULL };
    std::queue<std::string> messages;

    SDL_Texture *text{ nullptr };
    inline static SDL_Renderer *renderer{ nullptr };
    inline static TTF_Font *font{ nullptr };

    void (*finishedPrinting)(){ nullptr };

    TextBox();

public:
    TextBox(const TextBox &) = default;

    TextBox(TextBox &&) noexcept = default;

    TextBox &operator=(const TextBox &) = default;

    TextBox &operator=(TextBox &&) noexcept = default;

    ~TextBox() override;

    static TextBox &getInstance();

    static void init(SDL_Renderer *textRenderer, TTF_Font *textFont);

    void init(SDL_Rect newRect, int newBorder, int x, int y);

    void push(const char *message);

    void push(const std::string &message);

    void push(const std::vector<const char *> &toPush);

    void push(const std::vector<std::string> &toPush);

    void pop();

    void update() override;

    void render() const override;

    void setFinishedCallback(void (*instructions)());

    [[nodiscard]] bool empty() const;
};
