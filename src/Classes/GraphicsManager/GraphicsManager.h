//
// Created by Miles Youngblood on 12/5/2023.
//

#pragma once

#include "../Graphic/Graphic.h"

inline const SDL_Color BLACK{ 0, 0, 0, SDL_ALPHA_OPAQUE };
inline const SDL_Color WHITE{ 255, 255, 255, SDL_ALPHA_OPAQUE };

class GraphicsManager {
private:
    std::unordered_map<std::size_t, std::unique_ptr<Graphic>> graphics;

    GraphicsManager() = default;

public:
    static GraphicsManager &getInstance() {
        static GraphicsManager graphicsManager;
        return graphicsManager;
    }

    template<std::size_t n, typename T, typename ...Args>
    void addGraphic(Args ...args) {
        if (this->graphics.contains(n)) {
            std::clog << "This spot is already taken in graphics map!\n";
            return;
        }
        this->graphics.insert(std::make_pair(n, std::make_unique<T>(args...)));
    }

    void foo() {
        GraphicsManager::getInstance().addGraphic<4, Button>(WHITE, BLACK);
        GraphicsManager::getInstance().getGraphic<Button>(0);
    }

    void removeGraphic(std::size_t index) {
        try {
            this->graphics.erase(index);
        }
        catch (const std::out_of_range &e) {
            std::clog << "Error removing graphic: " << e.what() << '\n';
        }
    }

    template<typename G>
    G &getGraphic(std::size_t index) {
        try {
            Graphic *ptr = this->graphics.at(index).get();
            return *dynamic_cast<G *>(ptr);
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Error retrieving graphic: ") + e.what() + '\n');
        }
    }

    void render() {
        for (auto &graphic : this->graphics) {
            graphic.second->render();
        }
    }
};
