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

    std::atomic_bool running{ true };
    std::vector<bool> threadWaiting;

public:
    explicit ThreadPool(std::size_t n);

    ThreadPool(const ThreadPool &) = delete;

    ThreadPool(ThreadPool &&) noexcept = delete;

    ThreadPool &operator=(const ThreadPool &) = delete;

    ThreadPool &operator=(ThreadPool &&) noexcept = delete;

    ~ThreadPool();

    void add(std::function<void()> task);

    bool allThreadsWaiting();
};