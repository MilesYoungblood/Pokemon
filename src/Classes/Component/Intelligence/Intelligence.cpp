//
// Created by Miles Youngblood on 4/14/2024.
//

#include "../../Singleton/DerivedClasses/Game/Game.h"
#include "Intelligence.h"

Project::Intelligence::Intelligence(const std::function<void()> &action, const std::function<bool()> &condition,
                                    int (*delay)()) : action(action) {
    this->thoughtProcess = std::thread([this, condition, delay] -> void {
        std::mutex mutex;

        while (this->intelligent and Game::getInstance().isRunning()) {
            {
                std::unique_lock lock(mutex);
                this->cv.wait(lock, condition);
            }

            if (not this->intelligent or not Game::getInstance().isRunning()) {
                return;
            }

            if (not this->decisionMade) {
                this->decisionMade = true;
                Overworld::pushEvent();
            }

            std::unique_lock lock(mutex);
            this->cv.wait_for(lock, std::chrono::seconds(delay()), [] -> bool {
                return not Game::getInstance().isRunning();
            });
        }
    });
}

Project::Intelligence::~Intelligence() {
    this->intelligent = false;
    this->cv.notify_one();
    this->thoughtProcess.join();
}

void Project::Intelligence::tryActing() {
    if (this->decisionMade) {
        this->action();
        this->decisionMade = false;
    }
}

void Project::Intelligence::alert() {
    this->cv.notify_one();
}

