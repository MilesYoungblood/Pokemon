//
// Created by miles on 4/20/2024.
//

#include "Input.h"

namespace Component {
    void Input::setFunction(const SDL_Scancode x, const std::function<void()> &function) {
        this->functions[x] = function;
    }

    void Input::operator()(const SDL_Scancode x) const {
        if (not this->disabledCodes.contains(x)) {
            this->functions.at(x)();
        }
    }

    void Input::lock(const SDL_Scancode x) {
        this->disabledCodes.insert(x);
    }

    void Input::unlock(const SDL_Scancode x) {
        this->disabledCodes.erase(x);
    }

    void Input::lockAll() {
        for (auto &code : this->functions | std::views::keys) {
            this->disabledCodes.insert(code);
        }
    }

    void Input::unlockAll() {
        for (auto &code : this->functions | std::views::keys) {
            this->disabledCodes.erase(code);
        }
    }
}
