//
// Created by Miles Youngblood on 12/5/2023.
//

#include "TextBox.h"

TextBox::TextBox() {
    if (TextBox::font == nullptr) {
        throw std::runtime_error("Tried to construct textbox before class initialization");
    }
}

TextBox::~TextBox() {
    SDL_DestroyTexture(this->text);
    if (strlen(SDL_GetError()) > 0ULL) {
        std::clog << "Error destroying text: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
}

TextBox &TextBox::getInstance() {
    static TextBox textBox;
    return textBox;
}

void TextBox::init(SDL_Renderer *textRenderer, TTF_Font *textFont) {
    static bool initialized{ false };
    if (not initialized) {
        if (textRenderer == nullptr or textFont == nullptr) {
            throw std::runtime_error("One of the parameters of TextBox::init is null");
        }
        TextBox::renderer = textRenderer;
        TextBox::font = textFont;
    }

    initialized = true;
}

void TextBox::init(SDL_Rect newRect, int newBorder, int x, int y) {
    this->rect = newRect;
    this->textPos = std::make_pair(x, y);
    this->border = newBorder;
}

void TextBox::push(const char *message) {
    this->messages.emplace(message);
}

void TextBox::push(const std::string &message) {
    this->messages.push(message);
}

void TextBox::push(const std::vector<const char *> &toPush) {
    std::for_each(toPush.begin(), toPush.end(), [this](const char *message) -> void {
        this->messages.emplace(message);
    });
}

void TextBox::push(const std::vector<std::string> &toPush) {
    std::for_each(toPush.begin(), toPush.end(), [this](const std::string &message) -> void {
        this->messages.push(message);
    });
}

void TextBox::pop() {
    try {
        this->messages.pop();
        this->lettersPrinted = 0ULL;
    }
    catch (const std::exception &e) {
        std::clog << "Error popping message from queue: " << e.what() << '\n';
    }
}

void TextBox::update() {
    // if the message has not yet completed concatenation
    if (this->lettersPrinted <= this->messages.front().length()) {
        // safe delete the current text
        SDL_DestroyTexture(this->text);
        if (strlen(SDL_GetError()) > 0ULL) {
            std::clog << "Error destroying text: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }

        // buffer is required to store the substring
        // TODO eventually try to use src rect to display text rather than substr
        std::string buff;
        try {
            buff = this->messages.front();
        }
        catch (const std::exception &e) {
            std::clog << "Unexpected error: " << e.what() << '\n';
            return;
        }
        const std::string buffer{ this->lettersPrinted > 0 ? buff.substr(0, this->lettersPrinted) : " " };

        // recreate the text
        SDL_Surface *temp = TTF_RenderUTF8_Blended_Wrapped(TextBox::font, buffer.c_str(), Constants::Color::BLACK,
                                                           this->rect.w);
        this->text = SDL_CreateTextureFromSurface(TextBox::renderer, temp);

        // save the width and height of the text just in case next iteration, this branch isn't executed
        this->textWidth = temp->w;
        this->textHeight = temp->h;

        SDL_FreeSurface(temp);

        ++this->lettersPrinted;
    }
    else {
        if (this->finishedPrinting != nullptr) {
            this->finishedPrinting();
        }
    }
}

void TextBox::render() const {
    TextureManager::getInstance().drawRect(this->rect, Constants::Color::WHITE, Constants::Color::BLACK, border);

    TextureManager::getInstance().draw(this->text,
                                       { this->textPos.first, this->textPos.second, this->textWidth,
                                         this->textHeight });
}

void TextBox::setFinishedCallback(void (*instructions)()) {
    this->finishedPrinting = instructions;
}

bool TextBox::empty() const {
    return this->messages.empty();
}
