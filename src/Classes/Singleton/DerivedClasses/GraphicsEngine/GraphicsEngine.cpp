//
// Created by Miles Youngblood on 12/5/2023.
//

#include "GraphicsEngine.h"

void GraphicsEngine::update() {
    for (const auto &[fst, snd] : this->graphics) {
        std::vector<std::unique_ptr<Graphic>> &ref = this->graphics.at(fst);
        for (long long int i = 0; i < ref.size(); ++i) {
            if (ref.at(i)->isActive()) {
                ref.at(i)->update();
            }
            else {
                ref.erase(ref.cbegin() + i);
            }
        }
    }
}

void GraphicsEngine::render() const {
    for (const auto &[fst, snd] : this->graphics) {
        for (const auto &graphic : snd) {
            graphic->render();
        }
    }
}

void GraphicsEngine::clear() {
    for (auto &[fst, snd] : this->graphics) {
        snd.clear();
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
