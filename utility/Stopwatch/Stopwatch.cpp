//
// Created by Miles on 12/13/2023.
//

#include "Stopwatch.h"

void Stopwatch::start() {
    if (not this->active) {
        this->active = true;
        this->startTime = std::chrono::high_resolution_clock::now();
    }
}

void Stopwatch::stop() {
    if (this->active) {
        const auto stopTime = std::chrono::high_resolution_clock::now();
        this->elapsedTime += std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - this->startTime);
    }
    this->active = false;
}

void Stopwatch::reset() {
    this->elapsedTime = std::chrono::milliseconds(0);
    if (this->active) {
        this->startTime = std::chrono::high_resolution_clock::now();
    }
}

std::size_t Stopwatch::elapsed() const {
    if (this->active) {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const auto currentElapsedTime = this->elapsedTime + std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - this->startTime);
        return currentElapsedTime.count();
    }
    return this->elapsedTime.count();
}
