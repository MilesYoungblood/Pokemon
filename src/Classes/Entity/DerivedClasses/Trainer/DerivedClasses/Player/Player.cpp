//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

Player *Player::instancePtr = nullptr;
std::array<std::array<Pokemon *, 30>, 12> Player::pc;

Player::Player(const char *name, int x, int y, Direction direction) : Trainer(name, x, y) {
    this->setFrontModel(TextureManager::getInstance()->loadTexture(PROJECT_PATH + R"(\sprites\Hilbert_front.png)"));
    this->setBackModel(TextureManager::getInstance()->loadTexture(PROJECT_PATH + R"(\sprites\Hilbert_back.png)"));
    this->setLeftModel(TextureManager::getInstance()->loadTexture(PROJECT_PATH + R"(\sprites\Hilbert_left.png)"));
    this->setRightModel(TextureManager::getInstance()->loadTexture(PROJECT_PATH + R"(\sprites\Hilbert_right.png)"));

    this->setDirection(direction);

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

void Player::addToPc(Pokemon *toAdd) {
    for (auto &box : Player::pc) {
        for (auto &pokemon : box) {
            if (pokemon == nullptr) {
                pokemon = toAdd;
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
