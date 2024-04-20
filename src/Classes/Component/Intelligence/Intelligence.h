//
// Created by Miles Youngblood on 4/14/2024.
//

#pragma once

namespace Component {
    class Intelligence {
    public:
        Intelligence(const std::function<void()> &action, const std::function<bool()> &condition, int (*delay)());

        Intelligence(const Intelligence &) = delete;

        Intelligence(Intelligence &&) noexcept = delete;

        Intelligence &operator=(const Intelligence &) = delete;

        Intelligence &operator=(Intelligence &&) = delete;

        ~Intelligence();

        void tryActing();

    private:
        std::function<void()> action{ nullptr };

        std::atomic_bool ready{ false };
        std::atomic_bool intelligent{ true };

        std::thread thoughtProcess;
        std::condition_variable cv;
    };
}
