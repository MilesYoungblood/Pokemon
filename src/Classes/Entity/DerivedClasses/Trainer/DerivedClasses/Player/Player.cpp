//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

Player::Player() {
    this->setAnimation(Direction::UP, "sprites/Hilbert/HilbertSpriteSheetUp.png");
    this->setAnimation(Direction::DOWN, "sprites/Hilbert/HilbertSpriteSheetDown.png");
    this->setAnimation(Direction::LEFT, "sprites/Hilbert/HilbertSpriteSheetLeft.png");
    this->setAnimation(Direction::RIGHT, "sprites/Hilbert/HilbertSpriteSheetRight.png");
}

Player &Player::getPlayer() {
    static Player player;
    return player;
}

void Player::init(const char *name, int x, int y, Direction direction) {
    this->setName(name);
    this->setCoordinates(x, y);
    this->setDirection(direction);
}

void Player::addToPc(std::unique_ptr<Pokemon> toAdd) {
    for (auto &box : this->pc) {
        for (auto &pokemon : box) {
            if (pokemon == nullptr) {
                pokemon = std::move(toAdd);
            }
        }
    }
}

bool Player::canFight() const {
    return this->getFaintCount() < this->partySize();
}
