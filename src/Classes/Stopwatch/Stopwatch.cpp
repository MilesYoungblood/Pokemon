//
// Created by Miles on 12/13/2023.
//

#include "Stopwatch.h"

Stopwatch::~Stopwatch() {
    this->active = false;
}

void Stopwatch::start() {
    // prevents executing start if the stopwatch is still going
    if (this->active) {
        return;
    }

    this->active = true;
    this->counter = std::thread([this] -> void {
            while (this->active) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                ++this->elapsedTime;
            }
    });
    this->counter.detach();
}

void Stopwatch::stop() {
    this->active = false;
}

void Stopwatch::reset() {
    this->elapsedTime = 0ULL;
}

bool Stopwatch::operator<(std::size_t rhs) const {
    return this->elapsedTime < rhs;
}

bool Stopwatch::operator<=(std::size_t rhs) const {
    return this->elapsedTime <= rhs;
}

bool Stopwatch::operator>(std::size_t rhs) const {
    return this->elapsedTime > rhs;
}

bool Stopwatch::operator>=(std::size_t rhs) const {
    return this->elapsedTime >= rhs;
}

bool Stopwatch::operator==(std::size_t rhs) const {
    return this->elapsedTime == rhs;
}
