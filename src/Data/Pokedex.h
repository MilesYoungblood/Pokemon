//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../Classes/Pokemon/Pokemon.h"

struct Greninja : public Pokemon {
    Greninja(const std::initializer_list<Move*> &moves) : Pokemon("Greninja", Type::WATER, Type::DARK, 50, 300, 95, 67, 103, 71, 122, moves) {}
};

struct Charizard : public Pokemon {
    Charizard(const std::initializer_list<Move*> &moves) : Pokemon("Charizard", Type::FIRE, Type::FLYING, 50, 300, 84, 78, 109, 85, 100, moves) {}
};

struct Hydreigon : public Pokemon {
    Hydreigon(const std::initializer_list<Move*> &moves) : Pokemon("Hydreigon", Type::DARK, Type::DRAGON, 50, 300, 105, 90, 125, 90, 98, moves) {}
};

struct Pikachu : public Pokemon {
    Pikachu(const std::initializer_list<Move*> &moves) : Pokemon("Pikachu", Type::ELECTRIC, 50, 300, 55, 40, 50, 50, 90, moves) {}
};

struct Lucario : public Pokemon {
    Lucario(const std::initializer_list<Move*> &moves) : Pokemon("Lucario", Type::FIGHTING, Type::STEEL, 50, 300, 110, 70, 115, 70, 90, moves) {}
};