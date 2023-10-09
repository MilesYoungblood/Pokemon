//
// Created by Miles on 10/1/2023.
//

#include "Entity.h"

SDL_Renderer *Entity::renderer = nullptr;

Entity::Entity() : srcRect(), destRect() {
    this->x = 0;
    this->y = 0;
    this->vision = 1;
    this->direction = Direction::SOUTH;
    this->model = 'S';

    Entity::renderer = nullptr;
    this->texture = nullptr;
}

Entity::Entity(int x, int y) : Entity() {
    this->x = x;
    this->y = y;
}

Entity::Entity(int x, int y, const char *textureSheet, SDL_Renderer *r) : Entity(x, y) {
    Entity::renderer = r;
    this->texture = TextureManager::LoadTexture(textureSheet, r);
}

Entity::~Entity() {
    SDL_DestroyTexture(this->texture);
    //SDL_DestroyRenderer(Entity::renderer);
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
    this->model = 'N';
}

void Entity::faceEast() {
    this->direction = Entity::Direction::EAST;
    this->model = 'E';
}

void Entity::faceSouth() {
    this->direction = Entity::Direction::SOUTH;
    this->model = 'S';
}

void Entity::faceWest() {
    this->direction = Entity::Direction::WEST;
    this->model = 'W';
}

void Entity::setDirection(Entity::Direction newDirection) {
    this->direction = newDirection;
}

Entity::Direction Entity::getDirection() {
    return this->direction;
}

void Entity::setCoordinates(int newX, int newY) {
    this->x = newX;
    this->y = newY;
}

int Entity::getX() const {
    return this->x;
}

int Entity::getY() const {
    return this->y;
}

char Entity::getModel() const {
    return this->model;
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

void Entity::update(int x_pos, int y_pos) {
    this->destRect.h = 50;
    this->destRect.w = 50;

    this->destRect.x = x_pos;
    this->destRect.y = y_pos;
}

void Entity::render() {
    SDL_RenderCopy(Entity::renderer, this->texture, nullptr, &this->destRect);
}
