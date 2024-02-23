//
// Created by Miles Youngblood on 12/5/2023.
//

#include "TextBox.h"

TextBox::TextBox(SDL_Rect dest, int borderSize, int x, int y) {
    this->setDest(dest);
    this->textPos = std::make_pair(x, y);
    this->setBorderSize(borderSize);
}

TextBox::~TextBox() {
    SDL_DestroyTexture(this->text);
    if (strlen(SDL_GetError()) > 0) {
        std::clog << "Error destroying text: " << SDL_GetError() << '\n';
        SDL_ClearError();
    }
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
    this->messages.pop();
    this->lettersPrinted = 0;
}

void TextBox::update() {
    // if the message has not yet completed concatenation
    if (this->lettersPrinted <= this->messages.front().length()) {
        // safe delete the current text
        SDL_DestroyTexture(this->text);
        if (strlen(SDL_GetError()) > 0) {
            std::clog << "Error destroying text: " << SDL_GetError() << '\n';
            SDL_ClearError();
        }

        // buffer is required to store the substring
        // TODO eventually try to use src rect to display text rather than substr
        const std::string buff(this->messages.front());
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
    else if (this->finishedPrinting != nullptr) {
        this->finishedPrinting();
    }
}

void TextBox::render() const {
    TextureManager::getInstance().drawRect(this->getDest(), Constants::Color::WHITE, Constants::Color::BLACK,
                                           this->getBorderSize());

    TextureManager::getInstance().draw(
            this->text,
            SDL_Rect(this->textPos.first, this->textPos.second, this->textWidth, this->textHeight)
    );
}

void TextBox::setFinishedCallback(void (*instructions)()) {
    this->finishedPrinting = instructions;
}

bool TextBox::isPrinting() const {
    return this->lettersPrinted <= this->messages.front().length();
}

bool TextBox::empty() const {
    return this->messages.empty();
}
