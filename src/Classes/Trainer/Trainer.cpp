//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer() : items() {
    this->numFainted = 0;
    this->numPokemon = 0;
    this->x = 0;
    this->y = 0;
    this->range = 1;
    this->direction = directions::SOUTH;
    this->model = 'S';
}

Trainer::Trainer(const Trainer &toCopy) : items() {
    this->numFainted = toCopy.numFainted;
    this->numPokemon = toCopy.numPokemon;
    this->x = toCopy.x;
    this->y = toCopy.y;
    this->range = toCopy.range;
    this->direction = toCopy.direction;
    this->model = toCopy.model;
    for (int i = 0; i < toCopy.numPokemon; ++i) {
        this->party[i] = toCopy[i];
    }
}

Trainer::Trainer(const std::initializer_list<Pokemon> &pokemon, int x, int y) : items() {
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
    for (auto &type : items) {
        for (auto &item : type) {
            delete item;
        }
    }
}

int Trainer::partySize() const {
    return this->numPokemon;
}

Item& Trainer::getItem(int type, int item) {
    return *this->items[type][item];
}

void Trainer::setItems(const std::vector<std::vector<Item *>> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i == Trainer::MAX_ITEM_TYPES) {
            break;
        }
        for (int j = 0; j < v[i].size(); ++j) {
            if (j == Trainer::MAX_ITEMS) {
                break;
            }
            this->items[i][j] = v[i][j];
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

    return this->party[spot];
}

const Pokemon& Trainer::operator[](int spot) const {
    if (5 < spot or spot < 0)
        throw std::runtime_error("Index out of bounds");

    return this->party[spot];
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
void Trainer::face(const Trainer * t) {
    if (t->isFacingNorth()) {
        this->faceSouth();
    }
    else if (t->isFacingEast()) {
        this->faceWest();
    }
    else if (t->isFacingSouth()) {
        this->faceNorth();
    }
    else if (t->isFacingWest()) {
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
