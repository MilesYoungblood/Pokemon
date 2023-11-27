//
// Created by Miles Youngblood on 11/17/2023.
//

#pragma once

#include <memory>
#include <unordered_map>
#include <iostream>
#include <vector>
#include "../GameComponent/DerivedClasses/Components.h"

typedef int componentId;

class GameObject {
private:
    std::unordered_map<componentId , std::unique_ptr<GameComponent>> components;

    static componentId getComponentId() {
        static componentId lastId = 0;
        return lastId++;
    }

    template<typename C>
    static componentId getComponentId() {
        const static componentId component_id = GameObject::getComponentId();
        return component_id;
    }

public:
    static void init() {
        GameObject::getComponentId<PositionComponent>();
        GameObject::getComponentId<SpriteComponent>();
        GameObject::getComponentId<ResourceComponent>();
    }

    void update() {
        for (auto &component : this->components) {
            component.second->update();
        }
    }

    void render() {
        for (auto &component : this->components) {
            component.second->render();
        }
    }

    template<typename C, typename ...Args>
    void addComponent(Args ...args) {
        std::vector<std::unique_ptr<GameComponent>> comps;
        if (this->components.contains(GameObject::getComponentId<C>())) {
            comps.push_back(std::make_unique<C>(args...));
        }
        this->components.insert(std::make_pair(GameObject::getComponentId<C>(), std::make_unique<C>(args...)));
    }

    template<typename C>
    void removeComponent() {
        try {
            this->components.erase(GameObject::getComponentId<C>());
        }
        catch (const std::exception &e) {
            std::clog << "Trying to remove component that doesn't yet exist: " << e.what() << '\n';
        }
    }

    template<typename C>
    C &getComponent() {
        try {
            GameComponent *ptr = this->components.at(GameObject::getComponentId<C>()).get();
            return *static_cast<C *>(ptr);
        }
        catch (const std::exception &e) {
            throw std::runtime_error(
                    std::string("Trying to access component that doesn't yet exist: ") + e.what() + '\n');
        }
    }
};

inline void foo() {
    GameObject gameObject;
    gameObject.addComponent<PositionComponent>();
    gameObject.getComponent<PositionComponent>().translateX(6);
    gameObject.getComponent<PositionComponent>().translateY(6);
    std::cout << gameObject.getComponent<PositionComponent>().getX() << '\n';

    gameObject.addComponent<SpriteComponent>("sprites\\Hilbert\\HilbertSpriteSheetDown.png", 5, 1);
    gameObject.getComponent<SpriteComponent>().update();

    gameObject.addComponent<ResourceComponent>(100);
    gameObject.getComponent<ResourceComponent>().decrement(10);
    std::cout << gameObject.getComponent<ResourceComponent>().getCurrentAmount() << '\n';
}
