//
// Created by Miles Youngblood on 10/31/2023.
//

#pragma once

#include <iostream>
#include <thread>

template<typename Time>
class Stopwatch {
private:
    std::size_t elapsedTime{ 0ULL };

    bool active{ false };

    std::thread counter;

    void deactivate() {
        this->active = false;
        try {
            this->counter.detach();
        }
        catch (const std::exception &e) {
            std::clog << "Unable to detach thread: " << e.what() << '\n';
        }
    }

public:
    Stopwatch() = default;

    Stopwatch(const Stopwatch &) = delete;

    Stopwatch(Stopwatch &&) = delete;

    Stopwatch &operator=(const Stopwatch &) = delete;

    Stopwatch &operator=(Stopwatch &&) = delete;

    ~Stopwatch() {
        this->deactivate();
    }

    void start() {
        // prevents executing start if the timer is still going
        if (this->active) {
            return;
        }

        this->active = true;
        this->counter = std::thread([this] -> void {
            while (this->active) {
                std::this_thread::sleep_for(Time(1));
                ++this->elapsedTime;
            }
        });
    }

    void stop() {
        this->deactivate();
    }

    void reset() {
        this->elapsedTime = 0ULL;
    }

    bool operator<(std::size_t rhs) const {
        return this->elapsedTime < rhs;
    }

    bool operator<=(std::size_t rhs) const {
        return this->elapsedTime <= rhs;
    }

    bool operator >(std::size_t rhs) const {
        return this->elapsedTime > rhs;
    }

    bool operator >=(std::size_t rhs) const {
        return this->elapsedTime >= rhs;
    }

    bool operator==(std::size_t rhs) const {
        return this->elapsedTime == rhs;
    }
};
