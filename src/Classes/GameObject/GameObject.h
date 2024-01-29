//
// Created by Miles Youngblood on 11/17/2023.
//

#pragma once

#include "../GameComponent/DerivedClasses/Components.h"

class GameObject {
private:
    std::unordered_map<std::size_t, std::unique_ptr<GameComponent>> components;

public:
    GameObject() = default;

    template<typename C, typename ...Args>
    void addComponent(Args ...args) {
        if (not this->components.contains(typeid(C).hash_code())) {
            this->components.insert(std::make_pair(typeid(C).hash_code(), std::make_unique<C>(args...)));
        }
    }

    template<typename C>
    void removeComponent() {
        try {
            this->components.erase(typeid(C).hash_code());
        }
        catch (const std::exception &e) {
            std::clog << "Trying to remove component that doesn't yet exist: " << e.what() << '\n';
        }
    }

    template<typename C>
    C &getComponent() {
        try {
            GameComponent *ptr = this->components.at(typeid(C).hash_code()).get();
            return *dynamic_cast<C *>(ptr);
        }
        catch (const std::exception &e) {
            throw std::runtime_error(
                    std::string("Trying to access component that doesn't yet exist: ") + e.what() + '\n');
        }
    }
};

class EntityComponentSystem : public Singleton<EntityComponentSystem> {
private:
    std::unordered_map<int, std::unique_ptr<GameObject>> gameObjects;

    friend class Singleton<EntityComponentSystem>;

    EntityComponentSystem() = default;

public:
};

inline void foo() {
    GameObject gameObject;
    gameObject.addComponent<PositionComponent>(0, 0);
    gameObject.getComponent<PositionComponent>().translateX(6);
    gameObject.getComponent<PositionComponent>().translateY(6);
    std::cout << gameObject.getComponent<PositionComponent>().getX() << '\n';

    gameObject.addComponent<SpriteComponent>("sprites/Hilbert/HilbertSpriteSheetDown.png");
    gameObject.getComponent<SpriteComponent>().update();

    gameObject.addComponent<ResourceComponent>(100, 500);
    gameObject.getComponent<ResourceComponent>().decrement(10);
    std::cout << gameObject.getComponent<ResourceComponent>().getCurrentAmount() << '\n';
}
