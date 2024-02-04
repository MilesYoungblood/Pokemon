//
// Created by Miles on 11/28/2023.
//

#include "KeyManager.h"

KeyManager::KeyManager() {
    this->locker.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_W, false));
    this->locker.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_A, false));
    this->locker.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_S, false));
    this->locker.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_D, false));
    this->locker.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_RETURN, false));
    this->locker.insert(std::make_pair(SDL_Scancode::SDL_SCANCODE_ESCAPE, false));
}

void KeyManager::lockKey(SDL_Scancode key) {
    this->locker[key] = true;
}

void KeyManager::unlockKey(SDL_Scancode key) {
    this->locker[key] = false;
}

bool KeyManager::getKey(SDL_Scancode key) {
    const std::span key_states(SDL_GetKeyboardState(nullptr), 255ULL);
    return (key_states[key] != 0U) and not this->locker[key];
}
