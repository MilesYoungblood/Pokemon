//
// Created by Miles Youngblood on 4/14/2024.
//

#include "Intelligence.h"

Project::Intelligence::Intelligence(const std::function<bool()> &condition) {
    this->thoughtProcess = std::thread([this, condition] -> void {
        std::mutex mutex;

        while (this->intelligent) {
            std::unique_lock<std::mutex> lock(mutex);
            this->cv.wait(lock, condition);

            if (not this->intelligent) {
                return;
            }

            if (not this->decisionMade) {
                this->decisionMade = true;
            }
        }
    });
}

Project::Intelligence::~Intelligence() {
    this->intelligent = false;
    this->cv.notify_one();
    this->thoughtProcess.join();
}

void Project::Intelligence::act() {
    this->decision();
    this->decisionMade = false;
}
