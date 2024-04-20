//
// Created by Miles Youngblood on 10/30/2023.
//

#pragma once

#include "../Singleton.h"

// manages key-states
class KeyManager final : public Singleton<KeyManager> {
public:
    /// \brief locks a key
    /// \param key the key to lock
    void lock(SDL_Scancode key);

    /// \brief unlocks a key
    /// \param key the key to unlock
    void unlock(SDL_Scancode key);

    /// \brief updates all key states
    void update();

    /// \brief grabs the state of a key
    /// \param key the key to check
    /// \return true if the key is pressed and the key is not locked
    bool getKey(SDL_Scancode key);

private:
    std::span<const Uint8> keyStates;
    std::unordered_set<SDL_Scancode> lockedKeys;
    std::unordered_set<SDL_Scancode> heldKeys;
    bool acceptingHold{ true };

    friend class Singleton;

    KeyManager() = default;
};
