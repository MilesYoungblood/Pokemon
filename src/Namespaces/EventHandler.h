//
// Created by Miles Youngblood on 10/30/2023.
//

#pragma once

#include <unordered_map>
#include <vector>
#include <SDL.h>

// manages key-states
class EventHandler {
private:
    // container to represent key data (the state and if it is locked)
    struct data {
        bool state;
        bool locked;
    };

    const static std::size_t NUM_KEYS = 6;
    std::unordered_map<SDL_Scancode, data> keyStates;

    inline static EventHandler *instancePtr = nullptr;

    EventHandler() {
        this->keyStates[SDL_SCANCODE_W] = { false, false };
        this->keyStates[SDL_SCANCODE_A] = { false, false };
        this->keyStates[SDL_SCANCODE_S] = { false, false };
        this->keyStates[SDL_SCANCODE_D] = { false, false };
        this->keyStates[SDL_SCANCODE_RETURN] = { false, false };
        this->keyStates[SDL_SCANCODE_ESCAPE] = { false, false };
    }

public:
    static EventHandler *getInstance() {
        if (EventHandler::instancePtr == nullptr) {
            EventHandler::instancePtr = new EventHandler();
            std::cout << "EventHandler instance created!\n";
        }
        return EventHandler::instancePtr;
    }

    static void deleteInstance() {
        delete EventHandler::instancePtr;
        std::cout << "EventHandler instance deleted!\n";
    }

    // sets a key's state to down
    void KeyDown(SDL_Scancode key) {
        if (not this->keyStates[key].locked) {
            this->keyStates[key].state = true;
        }
        // erases the key if did not exist in the map
        if (this->keyStates.size() > NUM_KEYS) {
            this->keyStates.erase(key);
        }
    }

    // sets multiple key's states to down
    void KeyDown(const std::vector<SDL_Scancode> &keys) {
        for (const SDL_Scancode key : keys) {
            if (not this->keyStates[key].locked) {
                this->keyStates[key].state = true;
            }
            // erases the key if did not exist in the map
            if (this->keyStates.size() > NUM_KEYS) {
                this->keyStates.erase(key);
            }
        }
    }

    // sets a key's state to up
    void KepUp(SDL_Scancode key) {
        if (not this->keyStates[key].locked) {
            this->keyStates[key].state = false;
        }
        // erases the key if did not exist in the map
        if (this->keyStates.size() > NUM_KEYS) {
            this->keyStates.erase(key);
        }
    }

    // sets multiple key's states to up
    void KeyUp(const std::vector<SDL_Scancode> &keys) {
        for (const SDL_Scancode key : keys) {
            if (not this->keyStates[key].locked) {
                this->keyStates[key].state = false;
            }
            // erases the key if did not exist in the map
            if (this->keyStates.size() > NUM_KEYS) {
                this->keyStates.erase(key);
            }
        }
    }

    // locks a key
    void LockKey(SDL_Scancode key) {
        this->keyStates[key].locked = true;

        // erases the key if did not exist in the map
        if (this->keyStates.size() > NUM_KEYS) {
            this->keyStates.erase(key);
        }
        std::cout << this->keyStates.size() << '\n';
    }

    // locks multiple keys
    void BlockInput(const std::vector<SDL_Scancode> &keys) {
        for (const SDL_Scancode key : keys) {
            this->keyStates[key].locked = true;
            // erases the key if did not exist in the map
            if (this->keyStates.size() > NUM_KEYS) {
                this->keyStates.erase(key);
            }
        }
    }

    void UnlockKey(SDL_Scancode key) {
        this->keyStates[key].locked = false;

        // erases the key if did not exist in the map
        if (this->keyStates.size() > NUM_KEYS) {
            this->keyStates.erase(key);
        }
    }

    // unlocks multiple keys
    void EnableInput(const std::vector<SDL_Scancode> &keys) {
        for (const SDL_Scancode key : keys) {
            this->keyStates[key].locked = false;

            // erases the key if did not exist in the map
            if (this->keyStates.size() > NUM_KEYS) {
                this->keyStates.erase(key);
            }
        }
    }

    // returns true is a key is currently pressed
    bool GetKey(SDL_Scancode key) {
        const bool state = this->keyStates[key].state;

        // erases the key if did not exist in the map
        if (this->keyStates.size() > NUM_KEYS) {
            this->keyStates.erase(key);
        }

        return state;
    }
};
