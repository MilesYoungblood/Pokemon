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
        this->locked.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_W, false));
        this->locked.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_A, false));
        this->locked.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_S, false));
        this->locked.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_D, false));
        this->locked.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_RETURN, false));
        this->locked.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_ESCAPE, false));
    }

public:
    static KeyManager &getInstance() {
        static KeyManager keyManager;
        return keyManager;
    }

    /// Locks a key.
    /// \param key the key to lock.
    void lockKey(SDL_Scancode key) {
        this->locked.at(key) = true;
    }

    /// Locks all keys inside the KeyManager.
    void blockInput() {
        for (const std::pair<const SDL_Scancode, bool> &pair : this->locked) {
            this->locked[pair.first] = true;
        }
    }

    /// Locks WASD keys.
    void lockWasd() {
        this->locked[SDL_SCANCODE_W] = true;
        this->locked[SDL_SCANCODE_A] = true;
        this->locked[SDL_SCANCODE_S] = true;
        this->locked[SDL_SCANCODE_D] = true;
    }

    /// Unlocks WASD keys.
    void unlockWasd() {
        this->locked[SDL_SCANCODE_W] = false;
        this->locked[SDL_SCANCODE_A] = false;
        this->locked[SDL_SCANCODE_S] = false;
        this->locked[SDL_SCANCODE_D] = false;
    }

    /// Unlocks a key.
    /// \param key the key to unlock
    void unlockKey(SDL_Scancode key) {
        this->locked.at(key) = false;
    }

    /// Unlocks all keys inside the KeyManager.
    void enableInput() {
        for (const std::pair<const SDL_Scancode, bool> &pair : this->locked) {
            this->locked.at(pair.first) = false;
        }
    }

    /// Grabs the state of a key.
    /// \param direction direction that corresponds to a key
    /// \return true if the key is pressed and the key is not locked
    /// \throw std::invalid_argument by passing in an invalid direction
    bool getKey(Direction direction) {
        const std::span key_states(SDL_GetKeyboardState(nullptr), 255ULL);
        switch (direction) {
            case UP:
                return (key_states[SDL_SCANCODE_W] != 0U) and not this->locked[SDL_SCANCODE_W];
            case DOWN:
                return (key_states[SDL_SCANCODE_S] != 0U) and not this->locked[SDL_SCANCODE_S];
            case LEFT:
                return (key_states[SDL_SCANCODE_A] != 0U) and not this->locked[SDL_SCANCODE_A];
            case RIGHT:
                return (key_states[SDL_SCANCODE_D] != 0U) and not this->locked[SDL_SCANCODE_D];
            default:
                throw std::invalid_argument("Unexpected error: function getKey");
        }
    }

    /// Grabs the state of a key.
    /// \param key the key to check
    /// \return true if the key is pressed and the key is not locked
    bool getKey(SDL_Scancode key) {
        const std::span key_states(SDL_GetKeyboardState(nullptr), 255ULL);
        return (key_states[key] != 0U) and not this->locked[key];
    }

    /// Grabs the states of a set of keys.
    /// \param keys list of keys to check
    /// \return true if any of the keys are pressed and that key is not locked
    bool getKeys(const std::array<SDL_Scancode, KeyManager::NUM_KEYS> &keys) {
        return std::ranges::any_of(keys.begin(), keys.end(), [this](SDL_Scancode key) -> bool {
            const std::span key_states(SDL_GetKeyboardState(nullptr), 255ULL);
            return (key_states[key] != 0U) and not this->locked[key];
        });
    }
};
