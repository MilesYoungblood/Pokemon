//
// Created by Miles Youngblood on 3/9/2024.
//

#include "../Map/Map.h"
#include "Entity.h"

Entity::Entity(int mapX, int mapY) : map(mapX, mapY), screen(mapX * Map::TILE_SIZE, mapY * Map::TILE_SIZE) {}

Project::Position &Entity::getMapPosition() {
    return this->map;
}

Project::Position Entity::getMapPosition() const {
    return this->map;
}

Project::Position &Entity::getScreenPosition() {
    return this->screen;
}

Project::Position Entity::getScreenPosition() const {
    return this->screen;
}

bool Entity::isNextTo(const Entity *entity) const {
    return ((this->map.getY() == entity->map.getY() + 1 or this->map.getY() == entity->map.getY() - 1) and this->map.getX() == entity->map.getX()) or
           ((this->map.getX() == entity->map.getX() + 1 or this->map.getX() == entity->map.getX() - 1) and this->map.getY() == entity->map.getY());
}
