//
// Created by Miles Youngblood on 4/14/2024.
//

#include "../../Singleton/Game/Game.h"
#include "../../Singleton/EventHandler/EventHandler.h"
#include "Intelligence.h"

Component::Intelligence::Intelligence(const std::function<void()> &action, const std::function<bool()> &condition,
                                      int (*delay)()) : action(action) {
    this->thoughtProcess = std::thread([this, condition, delay] -> void {
        std::mutex mutex;

        while (this->intelligent and Game::getInstance().isRunning()) {
            {
                std::unique_lock lock(mutex);
                this->cv.wait(lock, [condition] -> bool { return condition() or not Game::getInstance().isRunning(); });
            }

            if (not this->intelligent or not Game::getInstance().isRunning()) {
                return;
            }

            if (not this->ready) {
                this->ready = true;
                EventHandler::pushEvent();
            }

            std::unique_lock lock(mutex);
            this->cv.wait_for(lock, std::chrono::seconds(delay()), [this] -> bool {
                return not this->intelligent or not Game::getInstance().isRunning();
            });
        }
    });
}

Component::Intelligence::~Intelligence() {
    this->intelligent = false;
    this->cv.notify_one();
    this->thoughtProcess.join();
}

void Component::Intelligence::tryActing() {
    if (this->ready) {
        this->action();
        this->ready = false;
    }
}

void Component::Intelligence::wakeUp() {
    this->cv.notify_one();
}
