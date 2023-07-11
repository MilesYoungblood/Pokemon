//
// Created by Miles Youngblood on 6/13/2022.
//

#include "Trainer.h"

Trainer::Trainer() {
    this->numFainted = 0;
    this->numPokemon = 0;
    this->x = 0;
    this->y = 0;
    this->direction = directions::SOUTH;
    this->model = 'S';
}

Trainer::Trainer(const std::initializer_list<Pokemon> &pokemon, int x, int y) {
    this->numFainted = 0;
    this->numPokemon= 0;

    this->x = x;
    this->y = y;
    this->direction = 3;
    this->model = 'S';

    for (const auto &p : pokemon) {
        if (this->numPokemon + 1 == Trainer::MAX_POKEMON)
            break;

        else {
            this->party[this->numPokemon] = p;
            ++this->numPokemon;
        }
    }
}

int Trainer::partySize() const {
    return this->numPokemon;
}

Item& Trainer::getItem(int item) {
    return this->items[item];
}

void Trainer::incFaintCount() {
    ++this->numFainted;
}

void Trainer::decFaintCount() {
    --this->numFainted;
}

void Trainer::defeat() {}

void Trainer::interact() {

}

void Trainer::move(int d) {
    switch (d) {
        case directions::NORTH:
            --this->y;
            break;
        case directions::EAST:
            ++this->x;
            break;
        case directions::SOUTH:
            ++this->y;
            break;
        case directions::WEST:
            --this->x;
            break;
        default:
            throw std::runtime_error("Broken");
    }
}

void Trainer::changeDirection(int d) {
    this->direction = d;

    switch (d) {
        case directions::NORTH:
            this->model = 'N';
            break;
        case directions::EAST:
            this->model = 'E';
            break;
        case directions::SOUTH:
            this->model = 'S';
            break;
        case directions::WEST:
            this->model = 'W';
            break;
        default:
            throw std::runtime_error("Broken");
    }
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

template<typename Object>
bool Trainer::isNextToNPC(const Object &npc) const {
    
}
