//
// Created by Miles on 10/1/2023.
//

#include "../Map/Map.h"
#include "Entity.h"

Entity::Entity(int x, int y)
        : x(x), y(y), screenX(x * Constants::TILE_SIZE), screenY(y * Constants::TILE_SIZE) {}

Entity::Entity(const char *name, int x, int y)
        : name(name), x(x), y(y), screenX(x * Constants::TILE_SIZE), screenY(y * Constants::TILE_SIZE) {}

void Entity::setName(const char *newName) {
    this->name = newName;
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
            dest.clear();
        }
        dest.append(buffer + ' ');
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

    this->screenX = this->x * Constants::TILE_SIZE;
    this->screenY = this->y * Constants::TILE_SIZE;
}

int Entity::getX() const {
    return this->x;
}

int Entity::getY() const {
    return this->y;
}

void Entity::moveForward() {
    switch (this->currentDirection) {
        case Direction::UP:
            --this->y;
            break;
        case Direction::RIGHT:
            ++this->x;
            break;
        case Direction::DOWN:
            ++this->y;
            break;
        case Direction::LEFT:
            --this->x;
            break;
    }
}

void Entity::setDirection(const Direction direction) {
    this->currentDirection = direction;
}

Direction Entity::getDirection() const {
    return this->currentDirection;
}

// makes this face the entity
void Entity::face(const Entity *entity) {
    try {
        this->setDirection(oppositeDirection(entity->getDirection()));
    }
    catch (const std::invalid_argument &e) {
        std::clog << "Error facing entity: " << e.what() << '\n';
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

bool Entity::canMoveForward(const Map *map) const {
    switch (this->currentDirection) {
        case Direction::UP:
            return not map->isObstructionHere(this->x, this->y - 1);
        case Direction::RIGHT:
            return not map->isObstructionHere(this->x + 1, this->y);
        case Direction::DOWN:
            return not map->isObstructionHere(this->x, this->y + 1);
        case Direction::LEFT:
            return not map->isObstructionHere(this->x - 1, this->y);
        default:
            throw std::runtime_error("Unexpected error: function canMoveForward");
    }
}

// returns true if this is right next to another entity, not necessarily facing
bool Entity::isNextTo(const Entity *entity) const {
    if (this->currentDirection == Direction::UP) {
        return this->y == entity->y + 1 and this->x == entity->x;
    }
    if (this->currentDirection == Direction::RIGHT) {
        return this->x == entity->x - 1 and this->y == entity->y;
    }
    if (this->currentDirection == Direction::DOWN) {
        return this->y == entity->y - 1 and this->x == entity->x;
    }
    if (this->currentDirection == Direction::LEFT) {
        return this->x == entity->x + 1 and this->y == entity->y;
    }
    return false;
}

bool Entity::hasVisionOf(const Entity *entity) const {
    // cannot see oneself
    if (this == entity) {
        return false;
    }
    if (this->currentDirection == Direction::UP) {
        return entity->getX() == this->x and entity->getY() < this->y and entity->getY() >= this->y - this->vision;
    }
    if (this->currentDirection == Direction::RIGHT) {
        return entity->getY() == this->y and entity->getX() > this->x and entity->getX() <= this->x + this->vision;
    }
    if (this->currentDirection == Direction::DOWN) {
        return entity->getX() == this->x and entity->getY() > this->y and entity->getY() <= this->y + this->vision;
    }
    if (this->currentDirection == Direction::LEFT) {
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

void Entity::setAnimation(Direction direction, const char *path, int numFrames, int numRows) {
    this->animations[direction] = Animation(path, numFrames, numRows);
}

void Entity::setAction(void (*function)(Entity *)) {
    this->action = function;
}

void Entity::act() {
    this->action(this);
}

void Entity::updateAnimation() {
    this->animations.at(this->currentDirection).update();
}

void Entity::render() {
    try {
        this->animations.at(this->currentDirection).render(
                { this->screenX, this->screenY, Constants::TILE_SIZE, Constants::TILE_SIZE });
    }
    catch (const std::out_of_range &e) {
        static int attempts = 1;
        std::clog << "(Attempt " << attempts++ << ") Error rendering animation: " << e.what() << '\n';
    }
}

void Entity::resetPos() {
    this->screenX = this->x * Constants::TILE_SIZE;
    this->screenY = this->y * Constants::TILE_SIZE;
}

Entity::operator bool() const {
    return false;
}
