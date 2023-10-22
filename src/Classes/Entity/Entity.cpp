//
// Created by Miles on 10/1/2023.
//

#include "Entity.h"

Entity::Entity() : destRect({ 0, 0, TILE_SIZE, TILE_SIZE }) {}

Entity::Entity(const int x, const int y) : x(x), y(y), destRect({ x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE }) {}

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

void Entity::moveForward() {
    switch (this->direction) {
        case NORTH:
            --this->y;
            break;
        case EAST:
            ++this->x;
            break;
        case SOUTH:
            ++this->y;
            break;
        case WEST:
            --this->x;
            break;
    }
}

void Entity::faceNorth() {
    this->direction = Direction::NORTH;
    this->currentModel = this->backModel;
}

void Entity::faceEast() {
    this->direction = Direction::EAST;
    this->currentModel = this->rightModel;
}

void Entity::faceSouth() {
    this->direction = Direction::SOUTH;
    this->currentModel = this->frontModel;
}

void Entity::faceWest() {
    this->direction = Direction::WEST;
    this->currentModel = this->leftModel;
}

void Entity::setDirection(Direction newDirection) {
    this->direction = newDirection;
}

auto Entity::getDirection() const -> Direction {
    return this->direction;
}

// sets the player's map coordinates and screen coordinates
void Entity::setCoordinates(const int newX, const int newY) {
    this->x = newX;
    this->y = newY;

    this->destRect.x = this->x * TILE_SIZE;
    this->destRect.y = this->y * TILE_SIZE;
}

auto Entity::getX() const -> int {
    return this->x;
}

auto Entity::getY() const -> int {
    return this->y;
}

auto Entity::isFacingNorth() const -> bool {
    return this->direction == Direction::NORTH;
}

auto Entity::isFacingEast() const -> bool {
    return this->direction == Direction::EAST;
}

auto Entity::isFacingSouth() const -> bool {
    return this->direction == Direction::SOUTH;
}

auto Entity::isFacingWest() const -> bool {
    return this->direction == Direction::WEST;
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
auto Entity::isNextTo(const Entity *entity) const -> bool {
    if (this->isFacingNorth()) {
        return this->y == entity->y + 1 and this->x == entity->x;
    }
    if (this->isFacingEast()) {
        return this->x == entity->x - 1 and this->y == entity->y;
    }
    if (this->isFacingSouth()) {
        return this->y == entity->y - 1 and this->x == entity->x;
    }
    if (this->isFacingWest()) {
        return this->x == entity->x + 1 and this->y == entity->y;
    }
    return false;
}

auto Entity::hasVisionOf(const Entity *entity) const -> bool {
    if (this->isFacingNorth()) {
        return entity->getX() == this->x and entity->getY() < this->y and entity->getY() >= this->y - this->vision;
    }
    if (this->isFacingEast()) {
        return entity->getY() == this->y and entity->getX() > this->x and entity->getX() <= this->x + this->vision;
    }
    if (this->isFacingSouth()) {
        return entity->getX() == this->x and entity->getY() > this->y and entity->getY() <= this->y + this->vision;
    }
    if (this->isFacingWest()) {
        return entity->getY() == this->y and entity->getX() < this->x and entity->getX() >= this->x - this->vision;
    }
    return false;
}

void Entity::setVision(int newVision) {
    this->vision = newVision;
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

void Entity::shiftDirectionOnMap(Direction direct, int distance) {
    switch (direct) {
        case Direction::NORTH:
            this->destRect.y -= distance;
            break;
        case Direction::EAST:
            this->destRect.x += distance;
            break;
        case Direction::SOUTH:
            this->destRect.y += distance;
            break;
        case Direction::WEST:
            this->destRect.x -= distance;
            break;
    }
}

auto Entity::getRect() const -> SDL_Rect {
    return this->destRect;
}

void Entity::setFrontModel(SDL_Texture *newFrontModel) {
    this->frontModel = newFrontModel;
}

void Entity::setBackModel(SDL_Texture *newBackModel) {
    this->backModel = newBackModel;
}

void Entity::setLeftModel(SDL_Texture *newLeftModel) {
    this->leftModel = newLeftModel;
}

void Entity::setRightModel(SDL_Texture *newRightModel) {
    this->rightModel = newRightModel;
}

void Entity::setCurrentModel(SDL_Texture *newCurrentModel) {
    this->currentModel = newCurrentModel;
}

auto Entity::getFrontModel() -> SDL_Texture * {
    return this->frontModel;
}

void Entity::render() {
    TextureManager::Draw(this->currentModel, this->destRect);
}

void Entity::resetPos() {
    this->destRect.x = this->x * TILE_SIZE;
    this->destRect.y = this->y * TILE_SIZE;
}
