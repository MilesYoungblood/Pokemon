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

void Entity::setDialogue(const char *text) {
    std::stringstream ss(text);

    const int CHARACTER_LIMIT = 0;
    int letterCounter = 0;
    std::string buffer;
    std::string dest;

    while (std::getline(ss, buffer, ' ')) {
        letterCounter += buffer.length();

        // if the next word exceeds the limit
        //if (letterCounter >= )
    }
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

void Entity::moveForward() {
    switch (this->currentDirection) {
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
    this->currentDirection = Direction::NORTH;
    this->currentModel = this->backModel;
}

void Entity::faceEast() {
    this->currentDirection = Direction::EAST;
    this->currentModel = this->rightModel;
}

void Entity::faceSouth() {
    this->currentDirection = Direction::SOUTH;
    this->currentModel = this->frontModel;
}

void Entity::faceWest() {
    this->currentDirection = Direction::WEST;
    this->currentModel = this->leftModel;
}

void Entity::setDirection(const Direction newDirection) {
    this->currentDirection = newDirection;

    switch (this->currentDirection) {
        case NORTH:
            this->currentModel = this->backModel;
            break;
        case EAST:
            this->currentModel = this->rightModel;
            break;
        case SOUTH:
            this->currentModel = this->frontModel;
            break;
        case WEST:
            this->currentModel = this->leftModel;
            break;
    }
}

Direction Entity::getDirection() const {
    return this->currentDirection;
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

bool Entity::isFacingNorth() const {
    return this->currentDirection == Direction::NORTH;
}

bool Entity::isFacingEast() const {
    return this->currentDirection == Direction::EAST;
}

bool Entity::isFacingSouth() const {
    return this->currentDirection == Direction::SOUTH;
}

bool Entity::isFacingWest() const {
    return this->currentDirection == Direction::WEST;
}

// returns true if this is right next to another entity, not necessarily facing
bool Entity::isNextTo(const Entity *entity) const {
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

bool Entity::hasVisionOf(const Entity *entity) const {
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

void Entity::shiftDirectionOnMap(Direction direction, int distance) {
    switch (direction) {
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

SDL_Rect Entity::getRect() const {
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

SDL_Texture * Entity::getFrontModel() {
    return this->frontModel;
}

void Entity::render() {
    TextureManager::Draw(this->currentModel, this->destRect);
}

void Entity::resetPos() {
    this->destRect.x = this->x * TILE_SIZE;
    this->destRect.y = this->y * TILE_SIZE;
}
