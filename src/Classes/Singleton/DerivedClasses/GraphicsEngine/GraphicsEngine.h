//
// Created by Miles Youngblood on 12/5/2023.
//

#pragma once

#include "../../../Graphic/DerivedClasses/Graphics.h"

class GraphicsEngine : public Singleton<GraphicsEngine> {
private:
    std::unordered_map<std::size_t, std::vector<std::unique_ptr<Graphic>>> graphics;

    friend class Singleton<GraphicsEngine>;

    GraphicsEngine();

public:
    template<typename G, typename ...Args>
    void addGraphic(Args ...args) {
        try {
            auto toAdd = std::make_unique<G>(args...);
            auto &set = this->graphics.at(typeid(G).hash_code());

            // necessary to prevent adding Singletons twice
            for (auto &graphic : set) {
                if (toAdd.get() == graphic.get()) {
                    return;
                }
            }
            set.push_back(std::move(toAdd));
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Error adding graphic: ") + e.what() + '\n');
        }
    }

    template<typename G>
    void removeGraphic(long long int index = 0) {
        try {
            std::size_t i = typeid(G).hash_code();
            this->graphics.at(i).erase(this->graphics.at(i).begin() + index);
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Error removing graphic: ") + e.what() + '\n');
        }
    }

    /// \brief gets a reference to a graphic
    /// \tparam G graphic type
    /// \param index index in the vector
    /// \return a reference to the graphic
    template<typename G>
    G &getGraphic(std::size_t index = 0) {
        try {
            Graphic *ptr = this->graphics.at(typeid(G).hash_code()).at(index).get();
            return *dynamic_cast<G *>(ptr);
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Error retrieving graphic: ") + e.what() + '\n');
        }
    }

    template<typename G>
    [[nodiscard]] bool hasAny() const {
        return this->graphics.at(typeid(G).hash_code()).empty();
    }

    void update();

    void render();
};
