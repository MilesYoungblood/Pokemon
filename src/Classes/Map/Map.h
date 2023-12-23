//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include "../Singleton/DerivedClasses/Camera/Camera.h"
#include "../Graphic/DerivedClasses/Texture/Texture.h"

class Map {
public:
    enum Id : Uint8 {
        NUVEMA_TOWN
    };

    struct ExitPoint {
        int x;                                // x-coordinate of the exit spot
        int y;                                // y-coordinate of the exit spot
        Map::Id newMap;                       // map that this exit point leads to
        int newX;                             // the player's new x-coordinates
        int newY;                             // the player's new y-coordinates
    };

    explicit Map(const char *name);

    Map(const Map &) = delete;

    Map(Map &&toMove) noexcept = delete;

    Map &operator=(const Map &) = delete;

    Map &operator=(Map &&rhs) noexcept = delete;

    ~Map() = default;

    static void loadTextures();

    [[nodiscard]] bool isObstructionHere(int x, int y) const;

    [[nodiscard]] std::optional<std::tuple<int, int, Map::Id>> isExitPointHere(int x, int y) const;

    template<typename ...Args>
    void addTrainer(Args ...args) {
        this->trainers.push_back(std::move(std::make_unique<Trainer>(args...)));
    }

    [[nodiscard]] int numTrainers() const;

    Trainer &operator[](int index);

    const Trainer &operator[](int index) const;

    std::vector<std::unique_ptr<Trainer>>::iterator begin();

    std::vector<std::unique_ptr<Trainer>>::iterator end();

    [[nodiscard]] std::string getMusic() const;

    void shift(Direction direction, int distance);

    void render() const;

    void reset();

private:
    using inventory = std::vector<std::pair<std::pair<int, int>, std::unique_ptr<Item>>>;

    const char *name{ "" };                             // name of the map

    std::string music;

    inline static Animation water;

    using tile = std::string;
    inline static std::unordered_map<tile, std::shared_ptr<Texture>> textureMap;

    using data = struct {
        std::string id;
        int x;
        int y;
    };

    using layer = std::vector<std::vector<data>>;
    std::vector<layer> layout;                      // The map is represented by a 2D int vector
    std::vector<std::vector<bool>> collision;

    std::vector<std::unique_ptr<Trainer>> trainers; // the set of trainers in this map

    inventory items;

    std::vector<Map::ExitPoint> exitPoints;         // coordinates where the player can leave this map to enter another

    [[nodiscard]] bool isTrainerHere(int x, int y) const;
};
