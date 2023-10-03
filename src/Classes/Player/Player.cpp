//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

Player * Player::instancePtr = nullptr;

Player::Player(int x, int y) : Trainer({}, x, y) {}

Player *Player::getPlayer(int x, int y) {
    if (Player::instancePtr == nullptr) {
        Player::instancePtr = new Player(x, y);
    }
    return Player::instancePtr;
}

void Player::destroyPlayer() {
    delete Player::instancePtr;
}
