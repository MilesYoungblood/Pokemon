//
// Created by Miles Youngblood on 3/9/2024.
//

#include "../Map/Map.h"
#include "Entity.h"

Entity::Entity(int mapX, int mapY) : mapX(mapX), mapY(mapY), screenX(mapX * Map::TILE_SIZE), screenY(mapY * Map::TILE_SIZE) {}

void Entity::setCoordinates(const int newX, const int newY) {
    this->mapX = newX;
    this->mapY = newY;

    this->screenX = this->mapX * Map::TILE_SIZE;
    this->screenY = this->mapY * Map::TILE_SIZE;
}

void Entity::translateX(int n) {
    this->mapX += n;
}

void Entity::translateY(int n) {
    this->mapY += n;
}

int Entity::getMapX() const {
    return this->mapX;
}

int Entity::getMapY() const {
    return this->mapY;
}

bool Entity::isNextTo(const Entity *entity) const {
    return (this->mapY == entity->mapY + 1 and this->mapX == entity->mapX) or (this->mapY == entity->mapY - 1 and this->mapX == entity->mapX) or
           (this->mapX == entity->mapX + 1 and this->mapY == entity->mapY) or (this->mapX == entity->mapX - 1 and this->mapY == entity->mapY);
}

void Entity::shiftHorizontally(int n) {
    this->screenX += n;
}

void Entity::shiftVertically(int n) {
    this->screenY += n;
}

void Entity::shift(Direction direction, int n) {
    switch (direction) {
        case Direction::UP:
            this->screenY -= n;
            break;
        case Direction::DOWN:
            this->screenY += n;
            break;
        case Direction::LEFT:
            this->screenX -= n;
            break;
        case Direction::RIGHT:
            this->screenX += n;
            break;
    }
}

int Entity::getScreenX() const {
    return this->screenX;
}

int Entity::getScreenY() const {
    return this->screenY;
}

void Entity::resetPos() {
    this->screenX = this->mapX * Map::TILE_SIZE;
    this->screenY = this->mapY * Map::TILE_SIZE;
}