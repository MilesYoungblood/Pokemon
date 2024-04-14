//
// Created by Miles Youngblood on 4/14/2024.
//

#pragma once

namespace Project {
    class Intelligence {
    private:
        void (*decision)(){ nullptr };

        std::atomic_bool decisionMade{ false };

        std::atomic_bool intelligent;
        std::thread thoughtProcess;
        std::condition_variable cv;

    public:
        explicit Intelligence(const std::function<bool()> &condition);

        Intelligence(const Intelligence &) = delete;

        Intelligence(Intelligence &&) noexcept = delete;

        Intelligence &operator=(const Intelligence &) = delete;

        Intelligence &operator=(Intelligence &&) = delete;

        ~Intelligence();

        void act();
    };
}
