//
// Created by Miles on 10/1/2023.
//

#include "Entity.h"

Entity::Entity(int x, int y) : name(), x(x), y(y), screenX(x * TILE_SIZE), screenY(y * TILE_SIZE) {
    this->action = [](Entity *) -> void {};
}

Entity::Entity(const char *name, const int x, const int y) : name(name), x(x), y(y), screenX(x * TILE_SIZE), screenY(y * TILE_SIZE) {
    this->action = [](Entity *) -> void {};
}

std::string Entity::getName() const {
    return this->name;
}

void Entity::setDialogue(const char *text) {
    std::stringstream ss(text);

    const int character_limit = 30;
    std::size_t letterCounter = 0;
    std::string buffer;
    std::string dest;

    while (std::getline(ss, buffer, ' ')) {
        letterCounter += buffer.length();

        // if the next word exceeds the limit
        if (letterCounter >= character_limit) {
            this->dialogue.push_back(dest);
            letterCounter = buffer.length();
            dest = "";
        }
        dest += buffer + ' ';
    }
    if (not dest.empty()) {
        this->dialogue.push_back(dest);
    }
}

std::vector<std::string> Entity::getDialogue() const {
    return this->dialogue;
}

// sets the player's map coordinates and screen coordinates
void Entity::setCoordinates(const int newX, const int newY) {
    this->x = newX;
    this->y = newY;

    this->screenX = this->x * TILE_SIZE;
    this->screenY = this->y * TILE_SIZE;
}

int Entity::getX() const {
    return this->x;
}

int Entity::getY() const {
    return this->y;
}

void Entity::moveForward() {
    switch (this->currentDirection) {
        case UP:
            --this->y;
            break;
        case RIGHT:
            ++this->x;
            break;
        case DOWN:
            ++this->y;
            break;
        case LEFT:
            --this->x;
            break;
    }
}

void Entity::faceNorth() {
    this->currentDirection = Direction::UP;
}

void Entity::faceEast() {
    this->currentDirection = Direction::RIGHT;
}

void Entity::faceSouth() {
    this->currentDirection = Direction::DOWN;
}

void Entity::faceWest() {
    this->currentDirection = Direction::LEFT;
}

void Entity::setDirection(const Direction newDirection) {
    this->currentDirection = newDirection;
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
    return this->currentDirection == Direction::UP;
}

bool Entity::isFacingEast() const {
    return this->currentDirection == Direction::RIGHT;
}

bool Entity::isFacingSouth() const {
    return this->currentDirection == Direction::DOWN;
}

bool Entity::isFacingWest() const {
    return this->currentDirection == Direction::LEFT;
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
    this->screenY -= distance;
}

void Entity::shiftDownOnMap(const int distance) {
    this->screenY += distance;
}

void Entity::shiftLeftOnMap(const int distance) {
    this->screenX -= distance;
}

void Entity::shiftRightOnMap(const int distance) {
    this->screenX += distance;
}

void Entity::shiftHorizontally(int distance) {
    this->screenX += distance;
}

void Entity::shiftVertically(int distance) {
    this->screenY += distance;
}

void Entity::shiftDirectionOnMap(Direction direction, int distance) {
    switch (direction) {
        case Direction::UP:
            this->screenY -= distance;
            break;
        case Direction::RIGHT:
            this->screenX += distance;
            break;
        case Direction::DOWN:
            this->screenY += distance;
            break;
        case Direction::LEFT:
            this->screenX -= distance;
            break;
    }
}

int Entity::getScreenX() const {
    return this->screenX;
}

int Entity::getScreenY() const {
    return this->screenY;
}

Entity::operator bool() const {
    return false;
}
