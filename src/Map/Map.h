//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include "../Component/Position/Position.h"
#include "../../../utility/ThreadPool/ThreadPool.h"
#include "../../../utility/Matrix/Matrix.h"

class Entity;

class Trainer;

class Map {
public:
    enum : Uint8 {
        TILE_SIZE = 80
    };

    Map(const char *name, const char *id);

    Map(const Map &) = delete;

    Map(Map &&toMove) noexcept = delete;

    Map &operator=(const Map &) = delete;

    Map &operator=(Map &&rhs) noexcept = delete;

    ~Map();

    /// \brief Checks to see if an obstruction is present
    /// \param x coordinate
    /// \param y coordinate
    /// \return true if a collision is here and false otherwise
    [[nodiscard]] bool isCollisionHere(int x, int y) const;

    /// \brief Checks to see if an exit point is present
    /// \param x coordinate
    /// \param y coordinate
    /// \return a pair containing the new position and new map respectively if an exit point is present, or nothing otherwise
    [[nodiscard]] std::optional<std::pair<Component::Position, std::string>> isExitPointHere(int x, int y) const;

    /// \brief Removes an entity from the map
    /// \param entity pointer to the entity to remove
    void removeEntity(const Entity *entity);

    /// \brief Getter for entity in entity vector
    /// \param index
    /// \return a reference to the Pokemon
    Entity &operator[](std::size_t index) const;

    /// \brief Allows for for-each loop functionality
    /// \return an iterator to the start of the entity vector
    std::vector<std::unique_ptr<Entity>>::iterator begin();

    /// \brief Allows for for-each loop functionality
    /// \return a const iterator to the start of the entity vector
    std::vector<std::unique_ptr<Entity>>::const_iterator begin() const;

    /// \brief Allows for for-each loop functionality
    /// \return an iterator to the end of the entity vector
    std::vector<std::unique_ptr<Entity>>::iterator end();

    /// \brief Allows for for-each loop functionality
    /// \return a const iterator to the end of the entity vector
    std::vector<std::unique_ptr<Entity>>::const_iterator end() const;

    /// \brief Getter for id
    /// \return the map's id
    [[nodiscard]] std::string getId() const;

    /// \brief Shifts all tiles and entities a certain direction and distance
    /// \param direction direction to shift
    /// \param n distance to shift
    void shift(Direction direction, int n);

    /// \brief Shifts all tiles and entities horizontally by some distance n
    /// \param n distance to shift
    void shiftHorizontally(int n);

    /// \brief Shifts all tiles and entities vertically by some distance n
    /// \param n distance to shift
    void shiftVertically(int n);

    /// \brief Renders all tiles and entities that are visible on the screen
    void render() const;

private:
    std::string name;
    std::string id;

    struct Tile {
        int id;
        Component::Position screen;
    };

    std::vector<Matrix<Tile>> layers;                               // The map is vector of Tile matrices
    std::vector<SDL_Texture *> tileSprites{ nullptr };              // texture for each tile id

    struct ExitPoint {
        Component::Position map;
        Component::Position dest;
        std::string newMap;                                         // map that this exit point leads to
    };

    std::vector<ExitPoint> exitPoints;                              // the set of exit points in the map

    std::unordered_set<int> collisionSet;                           // the set of tile ids that cause collision

    std::vector<std::unique_ptr<Entity>> entities;                  // the set of entities in the map
    ThreadPool threadPool;                                          // help speed up updating tiles and entities

    std::unordered_map<std::string, SDL_Texture *> entitySprites;   // mapping of entity sprites by id

    void parseTmx();

    void parseTsx(int firstGidAttribute, const std::string &sourceAttribute);

    void populate(const tinyxml2::XMLElement *mapElement, int width, int height);

    void loadEntities();

    void loadTrainer1(tinyxml2::XMLElement *entityElement);

    void loadTrainer2(std::unique_ptr<Trainer> &trainer, tinyxml2::XMLElement *visionElement);

    void loadItem(tinyxml2::XMLElement *entityElement);
};
