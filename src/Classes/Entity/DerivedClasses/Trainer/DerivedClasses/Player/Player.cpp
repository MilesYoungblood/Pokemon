//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

Player *Player::instancePtr = nullptr;
std::array<std::array<std::unique_ptr<Pokemon>, 30>, 12> Player::pc;

Player::Player(const char *name, int x, int y, Direction direction) : Trainer(name, x, y) {
    this->setDirection(direction);
    this->setUpAnimation(
            TextureManager::getInstance()->loadTexture(PROJECT_PATH + R"(\sprites\Hilbert\HilbertSpriteSheetUp.png)"),
            4, 1);
    this->setDownAnimation(
            TextureManager::getInstance()->loadTexture(PROJECT_PATH + R"(\sprites\Hilbert\HilbertSpriteSheetDown.png)"),
            4, 1);
    this->setLeftAnimation(
            TextureManager::getInstance()->loadTexture(PROJECT_PATH + R"(\sprites\Hilbert\HilbertSpriteSheetLeft.png)"),
            4, 1);
    this->setRightAnimation(
            TextureManager::getInstance()->loadTexture(PROJECT_PATH + R"(\sprites\Hilbert\HilbertSpriteSheetRight.png)"),
            4, 1);

    std::cout << "Player created!\n\n";
}

Player *Player::getPlayer(const char *name, int x, int y, Direction direction) {
    if (Player::instancePtr == nullptr) {
        Player::instancePtr = new Player(name, x, y, direction);
    }
    return Player::instancePtr;
}

void Player::destroyPlayer() {
    delete Player::instancePtr;
    Player::instancePtr = nullptr;
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
