//
// Created by Miles on 10/2/2023.
//

#include "Player.h"

Player * Player::instancePtr = nullptr;
Pokemon * Player::pc[12][30];

Player::Player(SDL_Renderer *renderer, int mapX, int mapY) : Trainer(mapX * TILE_SIZE, mapY * TILE_SIZE) {
    Player::renderer = renderer;

    this->destRect.x = mapX;
    this->destRect.y = mapY;

    //TODO remember to manually change path for now
    this->texture = TextureManager::LoadTexture(R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\Hilbert_front.png)", Player::renderer);
}

Player *Player::getPlayer(SDL_Renderer *renderer, int mapX, int mapY) {
    if (Player::instancePtr == nullptr) {
        Player::instancePtr = new Player(renderer, mapX, mapY);
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
