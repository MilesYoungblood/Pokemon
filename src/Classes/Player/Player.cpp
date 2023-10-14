//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

Player *Player::instancePtr = nullptr;
Pokemon *Player::pc[12][30];

Player::Player() : Trainer(1, 1) {
    const std::string path = std::filesystem::current_path().parent_path().generic_string() + R"(\sprites\Hilbert_)";

    this->frontModel = TextureManager::LoadTexture(path + "front.png");
    this->backModel = TextureManager::LoadTexture(path + "back.png");
    this->leftModel = TextureManager::LoadTexture(path + "left.png");
    this->rightModel = TextureManager::LoadTexture(path + "right.png");

    this->currentTexture = this->frontModel;

    this->destRect.x = this->x * TILE_SIZE;
    this->destRect.y = this->y * TILE_SIZE;
}

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
