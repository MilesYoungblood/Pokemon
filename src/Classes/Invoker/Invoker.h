//
// Created by Miles on 12/2/2023.
//

#pragma once

/// \brief A struct that immediately invokes a function upon instantiation (aka an IIFE in JavaScript)
struct Invoker {
    template<typename F, typename ...Args>
    Invoker(F f, Args ...args) {
        f(args...);
    }

    Invoker(const Invoker &) = delete;

    Invoker(Invoker &&) noexcept = delete;

    Invoker &operator=(const Invoker &) = delete;

    Invoker &operator=(Invoker &&) noexcept = delete;
};
