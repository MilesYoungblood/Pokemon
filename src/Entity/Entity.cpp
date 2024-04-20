//
// Created by Miles Youngblood on 3/9/2024.
//

#include "../Map/Map.h"
#include "Entity.h"

Entity::Entity(const char *id, const int x, const int y) : id(id), map(x, y), screen(x * Map::TILE_SIZE, y * Map::TILE_SIZE) {}

std::string Entity::getId() const {
    return this->id;
}

Component::Position &Entity::getMapPosition() {
    return this->map;
}

Component::Position Entity::getMapPosition() const {
    return this->map;
}

Component::Position &Entity::getScreenPosition() {
    return this->screen;
}

Component::Position Entity::getScreenPosition() const {
    return this->screen;
}

bool Entity::isNextTo(const Entity *entity) const {
    return ((this->map.getY() == entity->map.getY() + 1 or this->map.getY() == entity->map.getY() - 1) and this->map.getX() == entity->map.getX()) or
           ((this->map.getX() == entity->map.getX() + 1 or this->map.getX() == entity->map.getX() - 1) and this->map.getY() == entity->map.getY());
}
