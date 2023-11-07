//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

std::array<std::array<std::unique_ptr<Pokemon>, 30>, 12> Player::pc = std::array<std::array<std::unique_ptr<Pokemon>, 30>, 12>({ nullptr });

Player::Player() {
    this->setUpAnimation(
            TextureManager::getInstance().loadTexture(PROJECT_PATH + R"(\sprites\Hilbert\HilbertSpriteSheetUp.png)"),
            4, 1);
    this->setDownAnimation(
            TextureManager::getInstance().loadTexture(PROJECT_PATH + R"(\sprites\Hilbert\HilbertSpriteSheetDown.png)"),
            4, 1);
    this->setLeftAnimation(
            TextureManager::getInstance().loadTexture(PROJECT_PATH + R"(\sprites\Hilbert\HilbertSpriteSheetLeft.png)"),
            4, 1);
    this->setRightAnimation(
            TextureManager::getInstance().loadTexture(PROJECT_PATH + R"(\sprites\Hilbert\HilbertSpriteSheetRight.png)"),
            4, 1);
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
