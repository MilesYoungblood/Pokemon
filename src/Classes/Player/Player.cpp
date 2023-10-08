//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

Player * Player::instancePtr = nullptr;
Pokemon * Player::pc[12][30];

Player::Player() : Trainer(6, 8) {}

Player *Player::getPlayer() {
    if (Player::instancePtr == nullptr) {
        Player::instancePtr = new Player();
    }
    return Player::instancePtr;
}

void Player::destroyPlayer() {
    delete Player::instancePtr;
}

void Player::addToPC(Pokemon *toAdd) {
    for (auto &box : Player::pc) {
        for (auto &pokemon : box) {
            if (pokemon == nullptr) {
                pokemon = toAdd;
            }
        }
    }
}

Player::operator bool() const {
    return this->numFainted < this->numPokemon;
}

bool Player::canFight() const {
    return this->numFainted < this->numPokemon;
}
