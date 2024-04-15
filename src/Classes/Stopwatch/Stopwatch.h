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

    ~Stopwatch();

    void start();

    void stop();

    void reset();

    bool operator<(std::size_t rhs) const;

    bool operator<=(std::size_t rhs) const;

    bool operator>(std::size_t rhs) const;

    bool operator>=(std::size_t rhs) const;

    bool operator==(std::size_t rhs) const;

private:
    std::size_t elapsedTime{ 0 };

    bool active{ false };

    std::thread counter;
};
