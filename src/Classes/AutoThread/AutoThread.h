//
// Created by Miles on 12/2/2023.
//

#pragma once

/// \brief A struct that opens a thread and automatically detaches it
struct AutoThread {
    template<typename F, typename ...Args>
    AutoThread(F f, Args ...args) {
        std::thread thread(f, args...);
        thread.detach();
    }

    template<typename F, typename ...Args>
    static void run(F f, Args ...args) {
        std::thread thread(f, args...);
        thread.detach();
    }

    AutoThread(const AutoThread &) = delete;

    AutoThread(AutoThread &&) noexcept = delete;

    AutoThread &operator=(const AutoThread &) = delete;

    AutoThread &operator=(AutoThread &&) noexcept = delete;
};
