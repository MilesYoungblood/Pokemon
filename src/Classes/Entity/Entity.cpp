//
// Created by Miles on 10/1/2023.
//

#include "Entity.h"

Entity::Entity() : destRect({ 0, 0, TILE_SIZE, TILE_SIZE }) {
    this->x = 0;
    this->y = 0;
    this->vision = 1;
    this->direction = Direction::SOUTH;

    this->frontModel = nullptr;
    this->backModel = nullptr;
    this->leftModel = nullptr;
    this->rightModel = nullptr;

    this->currentTexture = nullptr;
}

Entity::Entity(const int x, const int y) : Entity() {
    this->x = x;
    this->y = y;

    this->destRect.x = this->x * TILE_SIZE;
    this->destRect.y = this->y * TILE_SIZE;
}

Entity::~Entity() {
    SDL_DestroyTexture(this->frontModel);
    SDL_DestroyTexture(this->backModel);
    SDL_DestroyTexture(this->leftModel);
    SDL_DestroyTexture(this->rightModel);
}

void Entity::moveNorth() {
    --this->y;
}

void Entity::moveEast() {
    ++this->x;
}

void Entity::moveSouth() {
    ++this->y;
}

void Entity::moveWest() {
    --this->x;
}

void Entity::faceNorth() {
    this->direction = Entity::Direction::NORTH;
    this->currentTexture = this->backModel;
}

void Entity::faceEast() {
    this->direction = Entity::Direction::EAST;
    this->currentTexture = this->rightModel;
}

void Entity::faceSouth() {
    this->direction = Entity::Direction::SOUTH;
    this->currentTexture = this->frontModel;
}

void Entity::faceWest() {
    this->direction = Entity::Direction::WEST;
    this->currentTexture = this->leftModel;
}

void Entity::setDirection(Entity::Direction newDirection) {
    this->direction = newDirection;
}

Entity::Direction Entity::getDirection() {
    return this->direction;
}

// sets the player's map coordinates and screen coordinates
void Entity::setCoordinates(const int newX, const int newY) {
    this->x = newX;
    this->y = newY;

    this->destRect.x = this->x * TILE_SIZE;
    this->destRect.y = this->y * TILE_SIZE;
}

int Entity::getX() const {
    return this->x;
}

int Entity::getY() const {
    return this->y;
}

bool Entity::isFacingNorth() const {
    return this->direction == Entity::Direction::NORTH;
}

bool Entity::isFacingEast() const {
    return this->direction == Entity::Direction::EAST;
}

bool Entity::isFacingSouth() const {
    return this->direction == Entity::Direction::SOUTH;
}

bool Entity::isFacingWest() const {
    return this->direction == Entity::Direction::WEST;
}

// makes this face the entity
void Entity::face(const Entity *entity) {
    if (entity->isFacingNorth()) {
        this->faceSouth();
    }
    else if (entity->isFacingEast()) {
        this->faceWest();
    }
    else if (entity->isFacingSouth()) {
        this->faceNorth();
    }
    else if (entity->isFacingWest()) {
        this->faceEast();
    }
}

// returns true if this is right next to another entity, not necessarily facing
bool Entity::isNextTo(const Entity *entity) const {
    if (this->isFacingNorth()) {
        return this->y == entity->y + 1 and this->x == entity->x;
    }
    else if (this->isFacingEast()) {
        return this->x == entity->x - 1 and this->y == entity->y;
    }
    else if (this->isFacingSouth()) {
        return this->y == entity->y - 1 and this->x == entity->x;
    }
    else if (this->isFacingWest()) {
        return this->x == entity->x + 1 and this->y == entity->y;
    }
    else {
        return false;
    }
}

bool Entity::hasVisionOf(const Entity *entity) const {
    if (this->isFacingNorth()) {
        return entity->getX() == this->x and entity->getY() < this->y and entity->getY() >= this->y - this->vision;
    }
    else if (this->isFacingEast()) {
        return entity->getY() == this->y and entity->getX() > this->x and entity->getX() <= this->x + this->vision;
    }
    else if (this->isFacingSouth()) {
        return entity->getX() == this->x and entity->getY() > this->y and entity->getY() <= this->y + this->vision;
    }
    else if (this->isFacingWest()) {
        return entity->getY() == this->y and entity->getX() < this->x and entity->getX() >= this->x - this->vision;
    }
    else {
        return false;
    }
}

void Entity::shiftUpOnMap(const int distance) {
    this->destRect.y -= distance;
}

void Entity::shiftDownOnMap(const int distance) {
    this->destRect.y += distance;
}

void Entity::shiftLeftOnMap(const int distance) {
    this->destRect.x -= distance;
}

void Entity::shiftRightOnMap(const int distance) {
    this->destRect.x += distance;
}

SDL_Rect Entity::getRect() const {
    return this->destRect;
}

void Entity::render() {
    TextureManager::Draw(this->currentTexture, this->destRect);
}

void Entity::resetPos() {
    this->destRect.x = this->x * TILE_SIZE;
    this->destRect.y = this->y * TILE_SIZE;
}
