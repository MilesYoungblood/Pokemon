//
// Created by miles on 4/20/2024.
//

#pragma once

namespace Component {
    class Input {
    public:
        Input() = default;

        Input(const Input &) = default;

        Input(Input &&) noexcept = default;

        Input &operator=(const Input &) = default;

        Input &operator=(Input &&) noexcept = default;

        ~Input() = default;

        void setFunction(SDL_Scancode x, const std::function<void()> &function);

        void operator()(SDL_Scancode x) const;

        void lock(SDL_Scancode x);

        void unlock(SDL_Scancode x);

        void lockAll();

        void unlockAll();

    private:
        std::unordered_map<SDL_Scancode, std::function<void()>> functions{};
        std::unordered_set<SDL_Scancode> disabledCodes{};
    };
}
