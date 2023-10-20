//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

Player *Player::instancePtr = nullptr;
Pokemon *Player::pc[12][30];

Player::Player() : Trainer(6, 8) {
    this->frontModel = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_front.png)");
    this->backModel = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_back.png)");
    this->leftModel = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_left.png)");
    this->rightModel = TextureManager::LoadTexture(PROJECT_PATH + R"(\sprites\Hilbert_right.png)");

    this->currentTexture = this->frontModel;

    this->destRect.x = this->x * TILE_SIZE;
    this->destRect.y = this->y * TILE_SIZE;

    std::cout << "Player created!\n\n";
}

Player *Player::getPlayer() {
    if (Player::instancePtr == nullptr) {
        Player::instancePtr = new Player();
    }
    return Player::instancePtr;
}

void Player::destroyPlayer() {
    delete Player::instancePtr;
    Player::instancePtr = nullptr;
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
