//
// Created by Miles Youngblood on 10/30/2023.
//

#pragma once

#include "../../Singleton.h"
#include "../../../Entity/Entity.h"

// manages key-states
class KeyManager : public Singleton<KeyManager> {
private:
    static const std::size_t NUM_KEYS{ 6 };

    std::unordered_map<SDL_Scancode, bool> locked;

    friend class Singleton<KeyManager>;

    KeyManager();

public:
    /// \brief Locks a key.
    /// \param key the key to lock.
    void lockKey(SDL_Scancode key);

    /// \brief Locks all keys inside the KeyManager.
    void blockInput();

    /// \brief Locks WASD keys.
    void lockWasd();

    /// \brief Unlocks WASD keys.
    void unlockWasd();

    /// \brief Unlocks a key.
    /// \param key the key to unlock
    void unlockKey(SDL_Scancode key);

    /// \brief Unlocks all keys inside the KeyManager.
    void enableInput();

    /// \brief Grabs the state of a key.
    /// \param direction direction that corresponds to a key
    /// \return true if the key is pressed and the key is not locked
    /// \throw std::invalid_argument by passing in an invalid direction
    bool getKey(Direction direction);

    /// \brief Grabs the state of a key.
    /// \param key the key to check
    /// \return true if the key is pressed and the key is not locked
    bool getKey(SDL_Scancode key);

    /// \brief Grabs the states of a set of keys.
    /// \param keys list of keys to check
    /// \return true if any of the keys are pressed and that key is not locked
    bool getKeys(const std::array<SDL_Scancode, KeyManager::NUM_KEYS> &keys);
};
