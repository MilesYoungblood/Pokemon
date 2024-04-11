//
// Created by Miles Youngblood on 4/10/2024.
//

#include "ThreadPool.h"

void ThreadPool::clean() {
    this->running = false;
    this->cv.notify_all();

    for (auto &worker : this->workers) {
        worker.join();
    }
}

ThreadPool::~ThreadPool() {
    this->clean();
}

void ThreadPool::init(std::size_t n) {
    // safe clean threads already here in case of re-initialization
    this->clean();
    this->running = true;

    for (std::size_t i = 0; i < n; ++i) {
        this->workers.emplace_back([this] -> void {
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
                    ++this->activeThreads;
                }

                task();

                std::scoped_lock<std::mutex> lock(this->mutex);
                --this->activeThreads;
                if (this->activeThreads == 0) {
                    this->allIdle.notify_one();
                }
            }
        });
    }
}

void ThreadPool::add(std::function<void()> task) {
    {
        std::scoped_lock<std::mutex> lock(this->mutex);
        this->tasks.push(std::move(task));
    }
    this->cv.notify_one();
}

void ThreadPool::block() {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->allIdle.wait(lock, [this] -> bool { return this->activeThreads == 0; });
}
