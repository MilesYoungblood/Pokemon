//
// Created by Miles Youngblood on 10/30/2023.
//

#pragma once

class KeyManager final {
public:
    /// \brief Getter for Singleton instance
    /// \return the KeyManager instance
    static KeyManager &getInstance();

    /// \brief Locks a key
    /// \param key the key to lock
    void lock(SDL_Scancode key);

    /// \brief Unlocks a key
    /// \param key the key to unlock
    void unlock(SDL_Scancode key);

    /// \brief Updates all key states
    void update();

    /// \brief Getter for key state
    /// \param key the key to check
    /// \return true if the key is pressed and the key is not locked
    bool getKey(SDL_Scancode key);

    /// \brief Sets the state if the KeyManager is allowing keys to be held
    /// \param x state
    void setHoldingState(bool x);

private:
    std::span<const Uint8> keyStates;
    std::unordered_set<SDL_Scancode> lockedKeys;
    std::unordered_set<SDL_Scancode> heldKeys;
    bool acceptingHold{ true };

    KeyManager() = default;
};
