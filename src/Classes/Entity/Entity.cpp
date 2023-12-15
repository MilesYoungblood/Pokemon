//
// Created by Miles on 10/1/2023.
//

#include "../Map/Map.h"
#include "Entity.h"

Entity::Entity(int x, int y) : x(x), y(y), screenX(x * Constants::TILE_SIZE), screenY(y * Constants::TILE_SIZE) {}

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

void Entity::setDialogue(const std::vector<std::string> &text) {
    for (const auto &i : text) {
        this->dialogue.push_back(i);
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
    this->setDirection(oppositeDirection(entity->getDirection()));
}

bool Entity::isFacing(Direction direction) const {
    return this->currentDirection == direction;
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
            throw std::invalid_argument("Invalid direction: canMoveForward()");
    }
}

// returns true if this is right next to another entity, not necessarily facing
bool Entity::isNextTo(const Entity *entity) const {
    switch (this->currentDirection) {
        case Direction::UP:
            return this->y == entity->y + 1 and this->x == entity->x;
        case Direction::DOWN:
            return this->y == entity->y - 1 and this->x == entity->x;
        case Direction::LEFT:
            return this->x == entity->x + 1 and this->y == entity->y;
        case Direction::RIGHT:
            return this->x == entity->x - 1 and this->y == entity->y;
        default:
            throw std::invalid_argument("Invalid direction: canMoveForward()");
    }
}

bool Entity::hasVisionOf(const Entity *entity) const {
    // cannot see oneself
    if (this == entity) {
        return false;
    }
    switch (this->currentDirection) {
        case Direction::UP:
            return entity->getX() == this->x and entity->getY() < this->y and entity->getY() >= this->y - this->vision;
        case Direction::DOWN:
            return entity->getX() == this->x and entity->getY() > this->y and entity->getY() <= this->y + this->vision;
        case Direction::LEFT:
            return entity->getY() == this->y and entity->getX() < this->x and entity->getX() >= this->x - this->vision;
        case Direction::RIGHT:
            return entity->getY() == this->y and entity->getX() > this->x and entity->getX() <= this->x + this->vision;
        default:
            throw std::invalid_argument("Invalid direction: canMoveForward()");
    }
}

void Entity::setVision(unsigned int newVision) {
    this->vision = newVision;
}

void Entity::shiftHorizontally(int distance) {
    this->screenX += distance;
}

void Entity::shiftVertically(int distance) {
    this->screenY += distance;
}

void Entity::shift(Direction direction, int distance) {
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

void Entity::setAnimation(Direction direction, const char *path) {
    this->animations[direction] = Animation(path);
}

void Entity::setAction(void (*function)(Entity *)) {
    this->action = function;
}

void Entity::act() {
    if (not this->isLocked) {
        try {
            this->action(this);
        }
        catch (const std::exception &e) {
            std::clog << "Error performing action: " << e.what() << '\n';
        }
    }
}

void Entity::lock() {
    this->isLocked = true;
}

void Entity::unlock() {
    this->isLocked = false;
}

void Entity::updateAnimation() {
    this->animations.at(this->currentDirection).update();
}

void Entity::render() const {
    this->animations.at(this->currentDirection).render(
            { this->screenX, this->screenY, Constants::TILE_SIZE, Constants::TILE_SIZE });
}

void Entity::resetPos() {
    this->screenX = this->x * Constants::TILE_SIZE;
    this->screenY = this->y * Constants::TILE_SIZE;
}

bool Entity::canFight() const {
    return false;
}
