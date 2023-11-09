//
// Created by Miles Youngblood on 10/30/2023.
//

#pragma once

#include <unordered_map>
#include <span>

// manages key-states
class KeyManager {
private:
    // container to represent key data (the state and if it is locked)
    struct Data {
        bool state;
        bool locked;
    };

    const static std::size_t NUM_KEYS{ 6 };

    std::unordered_map<SDL_Scancode, Data> keyStates;

    KeyManager() {
        this->keyStates[SDL_SCANCODE_W] = { false, false };
        this->keyStates[SDL_SCANCODE_A] = { false, false };
        this->keyStates[SDL_SCANCODE_S] = { false, false };
        this->keyStates[SDL_SCANCODE_D] = { false, false };
        this->keyStates[SDL_SCANCODE_RETURN] = { false, false };
        this->keyStates[SDL_SCANCODE_ESCAPE] = { false, false };
    }

public:
    static KeyManager &getInstance() {
        static KeyManager keyManager;
        return keyManager;
    }

    // sets a key's state to down
    void keyDown(SDL_Scancode key) {
        if (not this->keyStates.at(key).locked) {
            this->keyStates[key].state = true;
        }
    }

    // sets a key's state to up
    void keyUp(SDL_Scancode key) {
        if (not this->keyStates.at(key).locked) {
            this->keyStates[key].state = false;
        }
    }

    // locks a key
    void lockKey(SDL_Scancode key) {
        this->keyStates.at(key).state = false;
        this->keyStates.at(key).locked = true;
    }

    // locks multiple keys
    void blockInput(const std::array<SDL_Scancode, KeyManager::NUM_KEYS> &keys) {
        for (const SDL_Scancode key : keys) {
            this->keyStates.at(key).state = false;
            this->keyStates.at(key).locked = true;
        }
    }

    void lockWasd() {
        this->keyStates[SDL_SCANCODE_W].state = false;
        this->keyStates[SDL_SCANCODE_A].state = false;
        this->keyStates[SDL_SCANCODE_S].state = false;
        this->keyStates[SDL_SCANCODE_D].state = false;

        this->keyStates[SDL_SCANCODE_W].locked = true;
        this->keyStates[SDL_SCANCODE_A].locked = true;
        this->keyStates[SDL_SCANCODE_S].locked = true;
        this->keyStates[SDL_SCANCODE_D].locked = true;
    }

    void unlockWasd() {
        this->keyStates[SDL_SCANCODE_W].locked = false;
        this->keyStates[SDL_SCANCODE_A].locked = false;
        this->keyStates[SDL_SCANCODE_S].locked = false;
        this->keyStates[SDL_SCANCODE_D].locked = false;
    }

    void unlockKey(SDL_Scancode key) {
        this->keyStates.at(key).locked = false;
    }

    // unlocks multiple keys
    void enableInput(const std::array<SDL_Scancode, KeyManager::NUM_KEYS> &keys) {
        for (const SDL_Scancode key : keys) {
            this->keyStates.at(key).locked = false;
        }
    }

    bool getKey(Direction direction) {
        switch (direction) {
            case UP:
                return this->keyStates[SDL_SCANCODE_W].state;
            case DOWN:
                return this->keyStates[SDL_SCANCODE_S].state;
            case LEFT:
                return this->keyStates[SDL_SCANCODE_A].state;
            case RIGHT:
                return this->keyStates[SDL_SCANCODE_D].state;
            default:
                throw std::runtime_error("Unexpected error: function getKey");
        }
    }

    bool isLocked(SDL_Scancode key) {
        return this->keyStates.at(key).locked;
    }

    // returns true is a key is currently pressed
    bool getKey(SDL_Scancode key) {
        return this->keyStates.at(key).state;
    }

    bool get(SDL_Scancode key) {
        const std::span keys(SDL_GetKeyboardState(nullptr), 248ULL);
        return keys[key] == 1 and not this->keyStates[key].locked;
    }

    // returns true if any of the keys are currently pressed
    bool getKeys(const std::array<SDL_Scancode, KeyManager::NUM_KEYS> &keys) {
        return std::ranges::any_of(keys.begin(), keys.end(), [this](SDL_Scancode key) -> bool {
            return this->keyStates.at(key).state;
        });
    }
};
