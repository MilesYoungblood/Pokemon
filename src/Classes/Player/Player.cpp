//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

Player * Player::instancePtr = nullptr;

Player::Player() : Trainer(1, 1) {}

Player *Player::getPlayer() {
    if (Player::instancePtr == nullptr) {
        Player::instancePtr = new Player();
    }
    return Player::instancePtr;
}

void Player::destroyPlayer() {
    delete Player::instancePtr;
}

Player::operator bool() const {
    return this->numFainted < this->numPokemon;
}

bool Player::canFight() const {
    return this->numFainted < this->numPokemon;
}
