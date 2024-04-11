//
// Created by Miles Youngblood on 4/10/2024.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        this->workers.emplace_back([this, i] -> void {
                while (true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->mutex);
                        this->cv.wait(lock, [this] -> bool { return not this->running or not this->tasks.empty(); });

                        if (not this->running and this->tasks.empty()) {
                            return;
                        }

                        task = std::move(this->tasks.front());
                        this->tasks.pop();

                        this->threadWaiting.at(i) = false;
                    }

                    task();
                    std::scoped_lock<std::mutex> lock(this->mutex);
                    this->threadWaiting.at(i) = true;
                }
        });
    }

    this->threadWaiting = std::vector<bool>(n, true);
}

ThreadPool::~ThreadPool() {
    this->running.store(false, std::memory_order_release);
    this->cv.notify_all();

    for (auto &worker : this->workers) {
        worker.join();
    }
}

void ThreadPool::add(std::function<void()> task) {
    {
        std::scoped_lock<std::mutex> lock(this->mutex);
        if (this->running.load(std::memory_order_acquire)) {
            this->tasks.push(std::move(task));
        }
    }
    this->cv.notify_one();
}

bool ThreadPool::allThreadsWaiting() {
    std::scoped_lock<std::mutex> lock(this->mutex);
    return std::ranges::all_of(this->threadWaiting.begin(), this->threadWaiting.end(), [](bool val) -> bool {
        return val;
    });
}