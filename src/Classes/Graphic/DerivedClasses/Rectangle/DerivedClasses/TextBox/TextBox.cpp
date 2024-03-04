//
// Created by Miles Youngblood on 12/5/2023.
//

#include "TextBox.h"

TextBox::TextBox(SDL_Rect dest, int borderSize, int x, int y) : Rectangle(dest, borderSize){
    this->textPos = std::make_pair(x, y);
}

TextBox::~TextBox() {
    if (this->text != nullptr) {
        SDL_DestroyTexture(this->text);
        if (strlen(SDL_GetError()) > 0) {
            std::clog << "Error destroying text: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }
    }
}

void TextBox::push(const char *message, const std::function<void()> &function) {
    this->messageQueue.emplace(message);
    this->functionQueue.push(function);
}

void TextBox::push(const std::string &message, const std::function<void()> &function) {
    this->messageQueue.push(message);
    this->functionQueue.push(function);
}

void TextBox::push(const std::vector<const char *> &messages, const std::vector<std::function<void()>> &functions) {
    std::for_each(messages.begin(), messages.end(), [this](const char *message) -> void {
        this->messageQueue.emplace(message);
    });
    std::for_each(functions.begin(), functions.end(), [this](const std::function<void()> &function) -> void {
        this->functionQueue.emplace(function);
    });

}

void TextBox::push(const std::vector<std::string> &messages, const std::vector<std::function<void()>> &functions) {
    std::for_each(messages.begin(), messages.end(), [this](const std::string &message) -> void {
        this->messageQueue.push(message);
    });
    std::for_each(functions.begin(), functions.end(), [this](const std::function<void()> &function) -> void {
        this->functionQueue.emplace(function);
    });
}

void TextBox::pop() {
    if (not this->messageQueue.empty()) {
        this->messageQueue.pop();
        this->lettersPrinted = 0;
    }
    if (not this->functionQueue.empty()) {
        this->functionQueue.pop();
    }
}

void TextBox::update() {
    if (this->messageQueue.empty() or this->functionQueue.empty()) {
        return;
    }
    static bool called = false;
    // if the message has not yet completed concatenation
    if (this->lettersPrinted <= this->messageQueue.front().length()) {
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
        const std::string buff(this->messageQueue.front());
        const std::string buffer(this->lettersPrinted > 0 ? buff.substr(0, this->lettersPrinted) : " ");

        const auto data = TextureManager::getInstance().loadTextData(buffer, Constants::Color::BLACK,
                                                                     this->getDest().w);
        // recreate the text
        this->text = std::get<0>(data);

        // save the width and height of the text just in case next iteration, this branch isn't executed
        this->textWidth = std::get<1>(data);
        this->textHeight = std::get<2>(data);

        ++this->lettersPrinted;
    }
    else if (not called) {
        // TODO care; this could be causing a logic error with input of Return
        if (this->functionQueue.front() != nullptr) {
            this->functionQueue.front()();
        }
        called = true;
    }
}

void TextBox::render() const {
    this->renderBox();

    TextureManager::getInstance().draw(
            this->text,
            SDL_Rect(this->textPos.first, this->textPos.second, this->textWidth, this->textHeight)
    );
}

bool TextBox::isPrinting() const {
    return this->lettersPrinted <= this->messageQueue.front().length();
}

bool TextBox::empty() const {
    return this->messageQueue.empty();
}
