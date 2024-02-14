//
// Created by Miles Youngblood on 10/30/2023.
//

#pragma once

#include "../../Singleton.h"

// manages key-states
class KeyManager : public Singleton<KeyManager> {
private:
    std::unordered_map<SDL_Scancode, bool> locker;

    friend class Singleton<KeyManager>;

    KeyManager();

public:
    /// \brief Locks a key.
    /// \param key the key to lock.
    void lockKey(SDL_Scancode key);

    /// \brief Unlocks a key.
    /// \param key the key to unlock
    void unlockKey(SDL_Scancode key);

    /// \brief Grabs the state of a key.
    /// \param key the key to check
    /// \return true if the key is pressed and the key is not locked
    bool getKey(SDL_Scancode key);
};
