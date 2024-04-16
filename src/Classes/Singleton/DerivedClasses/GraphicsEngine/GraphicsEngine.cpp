//
// Created by Miles Youngblood on 12/5/2023.
//

#include "GraphicsEngine.h"

void GraphicsEngine::update() {
    for (auto &set : this->graphics | std::views::values) {
        for (long long int i = 0; i < set.size(); ++i) {
            if (set.at(i)->isActive()) {
                set.at(i)->update();
            }
            else {
                set.erase(set.cbegin() + i);
            }
        }
    }
}

void GraphicsEngine::render() const {
    for (auto &set : this->graphics | std::views::values) {
        for (const auto &graphic : set) {
            graphic->render();
        }
    }
}

void GraphicsEngine::clear() {
    for (auto &set : this->graphics | std::views::values) {
        set.clear();
    }
}

GraphicsEngine::GraphicsEngine() {
    this->graphics[typeid(Animation).hash_code()];
    this->graphics[typeid(Button).hash_code()];
    this->graphics[typeid(Panel).hash_code()];
    this->graphics[typeid(Rectangle).hash_code()];
    this->graphics[typeid(ResourceBar).hash_code()];
    this->graphics[typeid(SelectionBox).hash_code()];
    this->graphics[typeid(TextBox).hash_code()];
    this->graphics[typeid(Texture).hash_code()];
    this->graphics[typeid(TimedVisual).hash_code()];
}
