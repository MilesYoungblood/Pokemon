//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include "../Singleton/DerivedClasses/Camera/Camera.h"

class Map {
public:
    enum Id : Uint8 {
        ROUTE_1,
        ROUTE_2,
        ROUTE_3
    };

    struct ExitPoint {
        const int x;                                // x-coordinate of the exit spot
        const int y;                                // y-coordinate of the exit spot
        const Map::Id newMap;                       // map that this exit point leads to
        const int newX;                             // the player's new x-coordinates
        const int newY;                             // the player's new y-coordinates
    };

    Map();

    Map(const std::string &path, const char *music);

    Map(const char *name, const char *music, int width, int height);

    Map(const Map &toCopy) = delete;

    Map(Map &&toMove) noexcept;

    Map &operator=(const Map &) = delete;

    Map &operator=(Map &&) noexcept;

    ~Map();

    [[nodiscard]] bool isObstructionHere(int x, int y) const;

    void addExitPoint(const ExitPoint &exitPoint);

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

    void setObstruction(int x, int y);

    void shift(Direction direction, int distance);

    void render() const;

    void reset();

private:
    inline static int instanceCounter = 0;

    using inventory = std::vector<std::pair<std::pair<int, int>, std::unique_ptr<Item>>>;

    const char *name{ "" };                             // name of the map

    const char *music{ "" };

    inline static Animation water;

    using tile = int;
    inline static std::unordered_map<tile, SDL_Texture *> textureMap;

    using data = struct {
        int id;
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
