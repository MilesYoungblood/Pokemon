//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include "../../Enums/Direction/Direction.h"
#include "../ThreadPool/ThreadPool.h"
#include "../Matrix/Matrix.h"

class Entity;

class Trainer;

struct Sprite {
    struct Sheet {
        SDL_Texture *sprite{ nullptr };
        Uint32 numRows{ 0 };
        Uint32 numCols{ 0 };
    };
    int currentCol{ 0 };
    int currentRow{ 0 };
};

class Map {
public:
    enum : Uint8 {
        TILE_SIZE = 80
    };

    explicit Map(const char *name);

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
    /// \return a tuple containing the new coordinates and new map respectively if an exit point is present, or nothing otherwise
    [[nodiscard]] std::optional<std::tuple<int, int, std::string>> isExitPointHere(int x, int y) const;

    /// \brief Removes an entity from the map
    /// \param entity pointer to the entity to remove
    void removeEntity(Entity *entity);

    /// \brief Getter for entity in entity vector
    /// \param index
    /// \return a reference to the Pokemon
    Entity &operator[](std::size_t index);

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

    /// \brief Getter for music
    /// \return the music title
    [[nodiscard]] std::string getMusic() const;

    /// \brief Getter for an entity's sprite-sheet
    /// \param id id of the entity
    /// \return the sprite sheet of the respective entity
    [[nodiscard]] Sprite::Sheet getSpriteSheet(const std::string &id, Direction direction) const;

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
    std::string music;

    struct Tile {
        int id;
        int screenX;
        int screenY;
    };

    std::vector<Matrix<Map::Tile>> layout;                      // The map is vector of matrices

    std::unordered_set<int> collisionSet;                       // set of tile ids that cause collision
    std::vector<SDL_Texture *> tileImages{ nullptr };           // texture for each tile id

    std::vector<std::unique_ptr<Entity>> entities;              // the set of entities in this map
    ThreadPool threadPool;                                      // help speed up updating tiles and entities

    using spriteSet = std::array<Sprite::Sheet, 4>;             // a sprite sheet per cardinal direction
    std::unordered_map<std::string, spriteSet> entitySprites;   // mapping of entity sprites by id

    struct ExitPoint {
        int mapX;                                               // x-coordinate of the exit spot
        int mapY;                                               // y-coordinate of the exit spot
        int newMapX;                                            // the player's new x-coordinates
        int newMapY;                                            // the player's new y-coordinates
        std::string newMap;                                     // map that this exit point leads to
    };

    std::vector<Map::ExitPoint> exitPoints;                     // the set of exit points in the map

    void parseTmx();

    void parseTsx(int firstGidAttribute, const std::string &sourceAttribute);

    void populate(const tinyxml2::XMLElement *mapElement, int width, int height);

    void loadEntities();

    void loadTrainer1(tinyxml2::XMLElement *entityElement);

    void loadTrainer2(std::unique_ptr<Trainer> &trainer, tinyxml2::XMLElement *visionElement);

    void loadItem(tinyxml2::XMLElement *entityElement);
};
