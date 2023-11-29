//
// Created by Miles on 11/28/2023.
//

#include "KeyManager.h"

KeyManager::KeyManager() {
    this->locked.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_W, false));
    this->locked.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_A, false));
    this->locked.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_S, false));
    this->locked.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_D, false));
    this->locked.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_RETURN, false));
    this->locked.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_ESCAPE, false));
}

KeyManager &KeyManager::getInstance() {
    static KeyManager keyManager;
    return keyManager;
}

void KeyManager::lockKey(SDL_Scancode key) {
    this->locked.at(key) = true;
}

void KeyManager::blockInput() {
    for (const std::pair<const SDL_Scancode, bool> &pair : this->locked) {
        this->locked[pair.first] = true;
    }
}

void KeyManager::lockWasd() {
    this->locked[SDL_SCANCODE_W] = true;
    this->locked[SDL_SCANCODE_A] = true;
    this->locked[SDL_SCANCODE_S] = true;
    this->locked[SDL_SCANCODE_D] = true;
}

void KeyManager::unlockWasd() {
    this->locked[SDL_SCANCODE_W] = false;
    this->locked[SDL_SCANCODE_A] = false;
    this->locked[SDL_SCANCODE_S] = false;
    this->locked[SDL_SCANCODE_D] = false;
}

void KeyManager::unlockKey(SDL_Scancode key) {
    this->locked.at(key) = false;
}

void KeyManager::enableInput() {
    for (const std::pair<const SDL_Scancode, bool> &pair : this->locked) {
        this->locked.at(pair.first) = false;
    }
}

bool KeyManager::getKey(Direction direction) {
    const std::span key_states(SDL_GetKeyboardState(nullptr), 255ULL);
    switch (direction) {
        case Direction::UP:
            return (key_states[SDL_SCANCODE_W] != 0U) and not this->locked[SDL_SCANCODE_W];
        case Direction::DOWN:
            return (key_states[SDL_SCANCODE_S] != 0U) and not this->locked[SDL_SCANCODE_S];
        case Direction::LEFT:
            return (key_states[SDL_SCANCODE_A] != 0U) and not this->locked[SDL_SCANCODE_A];
        case Direction::RIGHT:
            return (key_states[SDL_SCANCODE_D] != 0U) and not this->locked[SDL_SCANCODE_D];
        default:
            throw std::invalid_argument("Unexpected error: function getKey");
    }
}

bool KeyManager::getKey(SDL_Scancode key) {
    const std::span key_states(SDL_GetKeyboardState(nullptr), 255ULL);
    return (key_states[key] != 0U) and not this->locked[key];
}

bool KeyManager::getKeys(const std::array<SDL_Scancode, KeyManager::NUM_KEYS> &keys) {
    return std::ranges::any_of(keys.begin(), keys.end(), [this](SDL_Scancode key) -> bool {
        const std::span key_states(SDL_GetKeyboardState(nullptr), 255ULL);
        return (key_states[key] != 0U) and not this->locked[key];
    });
}
