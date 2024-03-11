//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include "../Entity/DerivedClasses/Character/DerivedClasses/Trainer/Trainer.h"

class Map {
public:
    enum : Uint8 {
        TILE_SIZE = 80
    };

    struct ExitPoint {
        int x;                                // x-coordinate of the exit spot
        int y;                                // y-coordinate of the exit spot
        std::string newMap;                   // map that this exit point leads to
        int newX;                             // the player's new x-coordinates
        int newY;                             // the player's new y-coordinates
    };

    explicit Map(const char *name);

    Map(const Map &) = delete;

    Map(Map &&toMove) noexcept = default;

    Map &operator=(const Map &) = delete;

    Map &operator=(Map &&rhs) noexcept = default;

    ~Map();

    /// \brief Checks to see if an obstruction is present
    /// \param x coordinate
    /// \param y coordinate
    /// \return true if an obstruction is here and false otherwise
    [[nodiscard]] bool isObstructionHere(int x, int y) const;

    /// \brief Checks to see if an exit point is present
    /// \param x coordinate
    /// \param y coordinate
    /// \return a tuple containing the new coordinates and new map respectively if an exit point is present, or nothing otherwise
    [[nodiscard]] std::optional<std::tuple<int, int, std::string>> isExitPointHere(int x, int y) const;

    /// \brief Adds an entity to the map
    /// \param entity to add
    void addEntity(std::unique_ptr<Entity> entity);

    /// \brief Getter for entity vector size
    /// \return the number of entities in the map
    [[nodiscard]] std::size_t numEntities() const;

    /// \brief Getter for entity in entity vector
    /// \param index
    /// \return a reference to the Pokemon
    Entity &operator[](std::size_t index);

    /// \brief Allows for for-each loop functionality
    /// \return an iterator to the start of the entity vector
    std::vector<std::unique_ptr<Entity>>::iterator begin();

    /// \brief Allows for for-each loop functionality
    /// \return an iterator to the end of the entity vector
    std::vector<std::unique_ptr<Entity>>::iterator end();

    /// \brief Getter for music
    /// \return the music title
    [[nodiscard]] std::string getMusic() const;

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

    /// \brief Resets the positions of all tiles and entities
    void reset();

private:
    std::string name;
    std::string music;

    using tile = struct {
        int id;
        int x;
        int y;
    };

    using layer = std::vector<std::vector<tile>>;       // a layer is a 2D vector of data

    std::vector<layer> layout;                          // The map is vector of layers

    std::vector<bool> collision{ false };               // collision values for each tile id
    std::vector<SDL_Texture *> textures{ nullptr };     // texture for each tile id

    std::vector<std::unique_ptr<Entity>> entities;      // the set of entities in this map

    std::vector<Map::ExitPoint> exitPoints;             // coordinates where the player can leave this map to enter another

    void parseTmx();

    void parseTsx(const std::string &sourceAttribute);

    void populate(const tinyxml2::XMLElement *mapElement, int width, int height);

    void loadEntities();

    void loadTrainer1(tinyxml2::XMLElement *entityElement);

    void loadTrainer2(std::unique_ptr<Trainer> &trainer, tinyxml2::XMLElement *visionElement);

    void loadItem(tinyxml2::XMLElement *entityElement);
};
