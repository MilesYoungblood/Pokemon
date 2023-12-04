//
// Created by Miles Youngblood on 12/3/2023.
//

#include "GameObject.h"

GameObject::componentId GameObject::getComponentId() {
    static componentId lastId = 0;
    return lastId++;
}

void GameObject::init() {
    static bool initialized = false;

    if (initialized) {
        return;
    }

    GameObject::getComponentId<PositionComponent>();
    GameObject::getComponentId<SpriteComponent>();
    GameObject::getComponentId<ResourceComponent>();

    initialized = true;
}
