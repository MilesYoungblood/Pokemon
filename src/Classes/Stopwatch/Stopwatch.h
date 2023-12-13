//
// Created by Miles Youngblood on 10/31/2023.
//

#pragma once

template<typename Time>
class Stopwatch {
private:
    std::size_t elapsedTime{ 0 };

    bool active{ false };

    std::thread counter;

public:
    Stopwatch() = default;

    Stopwatch(const Stopwatch &) = delete;

    Stopwatch(Stopwatch &&) noexcept = delete;

    Stopwatch &operator=(const Stopwatch &) = delete;

    Stopwatch &operator=(Stopwatch &&) noexcept = delete;

    ~Stopwatch() {
        this->active = false;
    }

    void start() {
        // prevents executing start if the keyDelay is still going
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
        this->counter.detach();
    }

    void stop() {
        this->active = false;
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
