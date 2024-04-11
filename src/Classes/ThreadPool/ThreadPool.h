//
// Created by Miles Youngblood on 4/10/2024.
//

#pragma once

class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex mutex;
    std::condition_variable cv;
    std::condition_variable allIdle;

    std::atomic_bool running{ true };
    std::atomic_int activeThreads{ 0 };

    void clean();

public:
    ThreadPool() = default;

    ThreadPool(const ThreadPool &) = delete;

    ThreadPool(ThreadPool &&) noexcept = delete;

    ThreadPool &operator=(const ThreadPool &) = delete;

    ThreadPool &operator=(ThreadPool &&) noexcept = delete;

    ~ThreadPool();

    void init(std::size_t n);

    void add(std::function<void()> task);

    void block();
};