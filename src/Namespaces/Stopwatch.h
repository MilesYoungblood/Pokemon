//
// Created by Miles Youngblood on 10/31/2023.
//

#pragma once

#include <thread>

class Stopwatch {
private:
    std::size_t elapsedTime{ 0ULL };

    bool keepGoing{ false };

    std::thread counter;

    void deactivate() {
        this->keepGoing = false;
        try {
            this->counter.detach();
        }
        catch (const std::exception &e) {
            std::cerr << "Unable to detach thread: " << e.what() << '\n';
        }
    }

public:
    Stopwatch() = default;

    Stopwatch(const Stopwatch &) = delete;

    Stopwatch(const Stopwatch &&) = delete;

    Stopwatch &operator=(const Stopwatch &) = delete;

    Stopwatch &operator=(const Stopwatch &&) = delete;

    ~Stopwatch() {
        this->deactivate();
    }

    void start() {
        // prevents executing start if the timer is still going
        if (this->keepGoing) {
            return;
        }

        this->keepGoing = true;
        this->counter = std::thread([this] -> void {
            while (true) {
                if (not this->keepGoing) {
                    return;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                ++this->elapsedTime;
            }
        });
    }

    void stop() {
        // prevents executing stop if the timer is not going
        if (not this->keepGoing) {
            return;
        }

        this->deactivate();
    }

    void reset() {
        this->elapsedTime = 0ULL;
    }

    [[nodiscard]] std::size_t getElapsedTime() const {
        return this->elapsedTime;
    }
};
