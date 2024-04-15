//
// Created by Miles on 11/28/2023.
//

#include "KeyManager.h"

void KeyManager::lock(const SDL_Scancode key) {
    this->lockedKeys.insert(key);
}

void KeyManager::unlock(const SDL_Scancode key) {
    this->lockedKeys.erase(key);
}

void KeyManager::update() {
    SDL_PumpEvents();
    this->keyStates = std::span(SDL_GetKeyboardState(nullptr), 255);
}

bool KeyManager::getKey(const SDL_Scancode key) {
    if (this->lockedKeys.contains(key)) {
        return false;
    }
    if (this->keyStates[key] != 0U) {
        if (this->acceptingHold or not this->heldKeys.contains(key)) {
            this->heldKeys.insert(key);
            return true;
        }
        return false;
    }
    this->heldKeys.erase(key);
    return false;
}
