//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

Player * Player::instancePtr = nullptr;
Pokemon * Player::pc[12][30];

Player::Player(int mapX, int mapY) : Trainer(mapX * TILE_SIZE, mapY * TILE_SIZE) {
    this->destRect.x = mapX;
    this->destRect.y = mapY;

    std::string playerPath = desktop ?
        R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\)" :
        R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\)";

    this->frontModel = TextureManager::LoadTexture((playerPath + "Hilbert_front.png").c_str());
    this->backModel = TextureManager::LoadTexture((playerPath + "Hilbert_back.png").c_str());
    this->leftModel = TextureManager::LoadTexture((playerPath + "Hilbert_left.png").c_str());
    this->rightModel = TextureManager::LoadTexture((playerPath + "Hilbert_right.png").c_str());

    this->currentTexture = frontModel;
}

Player *Player::getPlayer(int mapX, int mapY) {
    if (Player::instancePtr == nullptr) {
        Player::instancePtr = new Player(mapX, mapY);
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
