//
// Created by Miles Youngblood on 10/30/2023.
//

#pragma once

#include <unordered_map>
#include <span>

// manages key-states
class KeyManager {
private:
    const static std::size_t NUM_KEYS{ 6 };

    std::unordered_map<SDL_Scancode, bool> locked;

    KeyManager() {
        this->locked[SDL_SCANCODE_W] = false;
        this->locked[SDL_SCANCODE_A] = false;
        this->locked[SDL_SCANCODE_S] = false;
        this->locked[SDL_SCANCODE_D] = false;
        this->locked[SDL_SCANCODE_RETURN] = false;
        this->locked[SDL_SCANCODE_ESCAPE] = false;
    }

public:
    static KeyManager &getInstance() {
        static KeyManager keyManager;
        return keyManager;
    }

    // locks a key
    void lockKey(SDL_Scancode key) {
        this->locked.at(key) = true;
    }

    // locks all keys inside the KeyManager
    void blockInput() {
        for (auto &pair : this->locked) {
            this->locked[pair.first] = true;
        }
    }

    void lockWasd() {
        this->locked[SDL_SCANCODE_W] = true;
        this->locked[SDL_SCANCODE_A] = true;
        this->locked[SDL_SCANCODE_S] = true;
        this->locked[SDL_SCANCODE_D] = true;
    }

    void unlockWasd() {
        this->locked[SDL_SCANCODE_W] = false;
        this->locked[SDL_SCANCODE_A] = false;
        this->locked[SDL_SCANCODE_S] = false;
        this->locked[SDL_SCANCODE_D] = false;
    }

    void unlockKey(SDL_Scancode key) {
        this->locked.at(key) = false;
    }

    // unlocks multiple keys
    void enableInput() {
        for (auto &pair : this->locked) {
            this->locked.at(pair.first) = false;
        }
    }

    bool getKey(Direction direction) {
        const std::span keyStates(SDL_GetKeyboardState(nullptr), 248ULL);
        switch (direction) {
            case UP:
                return keyStates[SDL_SCANCODE_W] and not this->locked[SDL_SCANCODE_W];
            case DOWN:
                return keyStates[SDL_SCANCODE_S] and not this->locked[SDL_SCANCODE_S];
            case LEFT:
                return keyStates[SDL_SCANCODE_A] and not this->locked[SDL_SCANCODE_A];
            case RIGHT:
                return keyStates[SDL_SCANCODE_D] and not this->locked[SDL_SCANCODE_D];
            default:
                throw std::runtime_error("Unexpected error: function getKey");
        }
    }

    bool getKey(SDL_Scancode key) {
        const std::span keyStates(SDL_GetKeyboardState(nullptr), 248ULL);
        return keyStates[key] == 1 and not this->locked[key];
    }

    // returns true if any of the keys are currently pressed
    bool getKeys(const std::array<SDL_Scancode, KeyManager::NUM_KEYS> &keys) {
        return std::ranges::any_of(keys.begin(), keys.end(), [this](SDL_Scancode key) -> bool {
            const std::span keyStates(SDL_GetKeyboardState(nullptr), 248ULL);
            return keyStates[key] == 1 and not this->locked[key];
        });
    }
};
