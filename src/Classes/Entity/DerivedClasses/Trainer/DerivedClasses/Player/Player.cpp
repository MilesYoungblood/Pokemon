//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

Player::Player() {
    this->setUpAnimation("sprites\\Hilbert\\HilbertSpriteSheetUp.png", 4, 1);
    this->setDownAnimation("sprites\\Hilbert\\HilbertSpriteSheetDown.png", 4, 1);
    this->setLeftAnimation("sprites\\Hilbert\\HilbertSpriteSheetLeft.png", 4, 1);
    this->setRightAnimation("sprites\\Hilbert\\HilbertSpriteSheetRight.png", 4, 1);
}

Player &Player::getPlayer() {
    static Player player;
    return player;
}

void Player::addToPc(std::unique_ptr<Pokemon> toAdd) {
    for (auto &box : Player::pc) {
        for (auto &pokemon : box) {
            if (pokemon == nullptr) {
                pokemon = std::move(toAdd);
            }
        }
    }
}

Player::operator bool() const {
    return this->getFaintCount() < this->partySize();
}

bool Player::canFight() const {
    return this->getFaintCount() < this->partySize();
}
