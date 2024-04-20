//
// Created by Miles Youngblood on 10/31/2023.
//

#pragma once

class Stopwatch {
public:
    Stopwatch() = default;

    Stopwatch(const Stopwatch &) = delete;

    Stopwatch(Stopwatch &&) noexcept = delete;

    Stopwatch &operator=(const Stopwatch &) = delete;

    Stopwatch &operator=(Stopwatch &&) noexcept = delete;

    ~Stopwatch() = default;

    void start();

    void stop();

    void reset();

    [[nodiscard]] std::size_t elapsed() const;

private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::milliseconds elapsedTime = std::chrono::milliseconds(0);

    bool active{ false };
};
