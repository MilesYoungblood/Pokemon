//
// Created by Miles Youngblood on 10/9/2023.
//

#pragma once

#include <cstdlib>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class E;

using ComponentID = size_t;

inline ComponentID getComponentTypeID() {
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

constexpr size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

struct Component {
    virtual ~Component() = default;

    E *entity = nullptr;
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
};

class E {
private:
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;

public:
    void update() {
        for (std::unique_ptr<Component> &component : this->components) {
            component->update();
        }
        for (std::unique_ptr<Component> &component : this->components) {
            component->draw();
        }
    }

    void draw() {

    }

    bool isActive() const {
        return this->active;
    }

    void destroy() {
        this->active = false;
    }

    template<typename T> bool hasComponent() const {
        return this->componentBitSet[getComponentTypeID<T>];
    }

    template<typename T, typename ... TArgs>
    T& addComponent(TArgs&&... mArgs) {
        T *c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        this->components.emplace_back(std::move(uPtr));

        this->componentArray[getComponentTypeID<T>()] = c;
        this->componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    template<typename T> T& getComponent() const {
        auto ptr(this->componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
};

class Manager {
private:
    std::vector<std::unique_ptr<E>> entities;

public:
    void update() {
        for (std::unique_ptr<E> &entity : this->entities) {
            entity->update();
        }
    }

    void draw() {
        for (std::unique_ptr<E> &entity : this->entities) {
            entity->draw();
        }
    }
    
    void refresh() {
        this->entities.erase(std::remove_if(std::begin(this->entities), std::end(this->entities),
            [](const std::unique_ptr<E> &mEntity) {
                return not mEntity->isActive();
        }), std::end(this->entities));
    }
};