//
// Created by Miles on 10/1/2023.
//

#pragma once

class Entity {
protected:
    enum Direction { NORTH, EAST, SOUTH, WEST };

    int x;                                  // x-coordinate on map
    int y;                                  // y-coordinate on map
    int vision;                             // line of sight
    char model;                             // visual representation of which way the trainer is facing
    Direction direction;                    // numerical representation of which way the trainer is facing

public:
    Entity();
    Entity(int x, int y);
    Entity(const Entity &toCopy) = delete;
    Entity& operator=(const Entity &toCopy) = delete;

    void moveNorth();
    void moveEast();
    void moveSouth();
    void moveWest();

    void faceNorth();
    void faceEast();
    void faceSouth();
    void faceWest();

    void setCoordinates(int newX, int newY);
    int getX() const;
    int getY() const;

    char getModel() const;

    bool isFacingNorth() const;
    bool isFacingEast() const;
    bool isFacingSouth() const;
    bool isFacingWest() const;

    void face(const Entity *entity);

    bool isNextTo(const Entity *entity) const;
    bool hasVisionOf(const Entity *entity) const;
};
