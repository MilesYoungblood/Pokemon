//
// Created by Miles Youngblood on 12/5/2023.
//

#include "../../../Singleton/TextureManager/TextureManager.h"
#include "TextBox.h"

TextBox::TextBox(const SDL_Rect dest, const int borderSize, const int x, const int y) : Rectangle(dest, borderSize), textBox(x, y, 0, 0) {}

TextBox::~TextBox() {
    if (this->text != nullptr) {
        SDL_DestroyTexture(this->text);
        if (strlen(SDL_GetError()) > 0) {
            std::clog << "Error destroying text: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }
}

void TextBox::push(const std::string &message, const std::function<void()> &function) {
    this->messageQueue.emplace(message, function);
}

void TextBox::push(const std::vector<std::pair<std::string, std::function<void()>>> &pairs) {
    std::ranges::for_each(pairs, [this](const std::pair<std::string, std::function<void()>> &pair) -> void {
        this->messageQueue.push(pair);
    });
}

void TextBox::pop() {
    if (not this->messageQueue.empty()) {
        this->messageQueue.pop();
        this->lettersPrinted = 0;
    }
}

void TextBox::update() {
    if (this->messageQueue.empty()) {
        return;
    }
    static bool called = false;
    // if the message has not yet completed concatenation
    if (this->lettersPrinted <= this->messageQueue.front().first.length()) {
        if (this->text != nullptr) {
            called = false;
            // safe delete the current text
            if (this->text != nullptr) {
                SDL_DestroyTexture(this->text);
                if (strlen(SDL_GetError()) > 0) {
                    std::clog << "Error destroying text: " << SDL_GetError() << '\n';
                    SDL_ClearError();
                }
            }
        }

        // buffer is required to store the substring
        // TODO eventually try to use src rect to display text rather than substr
        const std::string buff(this->messageQueue.front().first);
        const std::string buffer(this->lettersPrinted > 0 ? buff.substr(0, this->lettersPrinted) : " ");

        // recreate the text
        this->text = TextureManager::getInstance().loadWrappedText(buffer, Constants::Color::BLACK, this->getDest().w);

        // save the width and height of the text just in case next iteration, this branch isn't executed
        SDL_QueryTexture(this->text, nullptr, nullptr, &this->textBox.w, &this->textBox.h);

        ++this->lettersPrinted;
    }
    else if (not called) {
        // TODO care; this could be causing a logic error with input of Return
        if (this->messageQueue.front().second != nullptr) {
            this->messageQueue.front().second();
        }
        called = true;
    }
}

void TextBox::render() const {
    Rectangle::render();

    TextureManager::getInstance().draw(
            this->text,
            this->textBox
    );
}

bool TextBox::isPrinting() const {
    return this->lettersPrinted <= this->messageQueue.front().first.length();
}

bool TextBox::empty() const {
    return this->messageQueue.empty();
}
