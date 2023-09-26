//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer() : party(), items() {
    this->numFainted = 0;
    this->numPokemon = 0;

    this->x = 1;
    this->y = 1;
    this->range = 1;
    this->direction = directions::SOUTH;
    this->model = 'S';
}

Trainer::Trainer(const Trainer &toCopy) : party(), items() {
    this->numFainted = toCopy.numFainted;
    this->numPokemon = toCopy.numPokemon;

    this->x = toCopy.x;
    this->y = toCopy.y;
    this->range = toCopy.range;
    this->direction = toCopy.direction;
    this->model = toCopy.model;

    for (int i = 0; i < toCopy.numPokemon; ++i) {
        this->party[i] = toCopy.party[i];
    }

    for (int i = 0; i < Trainer::MAX_ITEM_TYPES; ++i) {
        for (int j = 0; j < Trainer::MAX_ITEMS; ++j) {
            this->items[i][j] = toCopy.items[i][j];
        }
    }
}

Trainer::Trainer(const std::initializer_list<Pokemon*> &pokemon, int x, int y) : party(), items() {
    this->numFainted = 0;
    this->numPokemon= 0;

    this->x = x;
    this->y = y;
    this->range = 1;
    this->direction = 3;
    this->model = 'S';

    for (const auto &p : pokemon) {
        if (this->numPokemon == Trainer::MAX_POKEMON)
            break;

        else {
            this->party[this->numPokemon] = p;
            ++this->numPokemon;
        }
    }
}

Trainer::~Trainer() {
    for (auto &type : this->items) {
        for (auto &item : type) {
            delete item;
        }
    }
}

Trainer& Trainer::operator=(const Trainer &rhs) {
    if (this != &rhs) {
        this->numFainted = rhs.numFainted;
        this->numPokemon = rhs.numPokemon;
        this->x = rhs.x;
        this->y = rhs.y;
        this->range = rhs.range;
        this->direction = rhs.direction;
        this->model = rhs.model;

        for (auto &pokemon : this->party) {
            delete pokemon;
        }
        for (int i = 0; i < rhs.numPokemon; ++i) {
            this->party[i] = rhs.party[i];
        }

        for (auto &item : this->items) {
            for (auto &j : item) {
                delete j;
            }
        }
        for (int i = 0; i < Trainer::MAX_ITEM_TYPES; ++i) {
            for (int j = 0; j < Trainer::MAX_ITEMS; ++j) {
                this->items[i][j] = rhs.items[i][j];
            }
        }
    }
    return *this;
}

int Trainer::partySize() const {
    return this->numPokemon;
}

Item& Trainer::getItem(int type, int item) {
    return *this->items[type][item];
}

void Trainer::setItems(const std::vector<std::vector<Item *>> &inventory) {
    for (int i = 0; i < inventory.size(); ++i) {
        if (i == Trainer::MAX_ITEM_TYPES) {
            break;
        }
        for (int j = 0; j < inventory[i].size(); ++j) {
            if (j == Trainer::MAX_ITEMS) {
                break;
            }
            this->items[i][j] = inventory[i][j];
        }
    }
}

void Trainer::incFaintCount() {
    ++this->numFainted;
}

void Trainer::decFaintCount() {
    --this->numFainted;
}

void Trainer::defeat() {}

void Trainer::moveNorth() {
    --this->y;
}

void Trainer::moveEast() {
    ++this->x;
}

void Trainer::moveSouth() {
    ++this->y;
}

void Trainer::moveWest() {
    --this->x;
}

void Trainer::faceNorth() {
    this->direction = directions::NORTH;
    this->model = 'N';
}

void Trainer::faceEast() {
    this->direction = directions::EAST;
    this->model = 'E';
}

void Trainer::faceSouth() {
    this->direction = directions::SOUTH;
    this->model = 'S';
}

void Trainer::faceWest() {
    this->direction = directions::WEST;
    this->model = 'W';
}

Pokemon& Trainer::operator[](int spot)  {
    if (5 < spot or spot < 0)
        throw std::runtime_error("Index out of bounds");

    return *this->party[spot];
}

const Pokemon& Trainer::operator[](int spot) const {
    if (5 < spot or spot < 0)
        throw std::runtime_error("Index out of bounds");

    return *this->party[spot];
}

void Trainer::setCoordinates(int xCoord, int yCoord) {
    this->x = xCoord;
    this->y = yCoord;
}

int Trainer::getX() const {
    return this->x;
}

int Trainer::getY() const {
    return this->y;
}

char Trainer::getModel() const {
    return this->model;
}

bool Trainer::canFight() const {
    return this->numFainted < this->numPokemon;
}

bool Trainer::isFacingNorth() const {
    return this->direction == directions::NORTH;
}

bool Trainer::isFacingEast() const {
    return this->direction == directions::EAST;
}

bool Trainer::isFacingSouth() const {
    return this->direction == directions::SOUTH;
}

bool Trainer::isFacingWest() const {
    return this->direction == directions::WEST;
}

bool Trainer::hasVisionOf(const Trainer * t) const {
    if (this->isFacingNorth()) {
        return t->getX() == this->x and t->getY() < this->y and t->getY() >= this->y - this->range;
    }
    else if (this->isFacingEast()) {
        return t->getY() == this->y and t->getX() > this->x and t->getX() <= this->x + this->range;
    }
    else if (this->isFacingSouth()) {
        return t->getX() == this->x and t->getY() > this->y and t->getY() <= this->y + this->range;
    }
    else if (this->isFacingWest()) {
        return t->getY() == this->y and t->getX() < this->x and t->getX() >= this->x -  this->range;
    }
    else {
        return false;
    }
}

// makes this face the trainer
void Trainer::face(const Trainer * trainer) {
    if (trainer->isFacingNorth()) {
        this->faceSouth();
    }
    else if (trainer->isFacingEast()) {
        this->faceWest();
    }
    else if (trainer->isFacingSouth()) {
        this->faceNorth();
    }
    else if (trainer->isFacingWest()) {
        this->faceEast();
    }
}

// returns true if this is right next to another trainer, not necessarily facing
bool Trainer::isNextTo(const Trainer * trainer) const {
    if (this->isFacingNorth()) {
        return this->y == trainer->y + 1 and this->x == trainer->x;
    }
    else if (this->isFacingEast()) {
        return this->x == trainer->x - 1 and this->y == trainer->y;
    }
    else if (this->isFacingSouth()) {
        return this->y == trainer->y - 1 and this->x == trainer->x;
    }
    else if (this->isFacingWest()) {
        return this->x == trainer->x + 1 and this->y == trainer->y;
    }
    else {
        return false;
    }
}
