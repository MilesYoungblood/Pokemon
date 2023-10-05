//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../Classes/Pokemon/Pokemon.h"

struct Charizard : public Pokemon {
    Charizard() : Pokemon("Charizard", Type::FIRE, Type::FLYING, 50, 300, 84, 78, 109, 85, 100) {}
    Charizard(const std::initializer_list<Move*> &moves) : Pokemon("Charizard", Type::FIRE, Type::FLYING, 50, 300, 84, 78, 109, 85, 100, moves) {}

    PokemonID getID() override {
        return PokemonID::CHARIZARD;
    }
};

struct Pikachu : public Pokemon {
    Pikachu() : Pokemon("Pikachu", Type::ELECTRIC, 50, 300, 55, 40, 50, 50, 90) {}
    Pikachu(const std::initializer_list<Move*> &moves) : Pokemon("Pikachu", Type::ELECTRIC, 50, 300, 55, 40, 50, 50, 90, moves) {}

    PokemonID getID() override {
        return PokemonID::PIKACHU;
    }
};

struct Lucario : public Pokemon {
    Lucario() : Pokemon("Lucario", Type::FIGHTING, Type::STEEL, 50, 300, 110, 70, 115, 70, 90) {}
    Lucario(const std::initializer_list<Move*> &moves) : Pokemon("Lucario", Type::FIGHTING, Type::STEEL, 50, 300, 110, 70, 115, 70, 90, moves) {}

    PokemonID getID() override {
        return PokemonID::LUCARIO;
    }
};

struct Hydreigon : public Pokemon {
    Hydreigon() : Pokemon("Hydreigon", Type::DARK, Type::DRAGON, 50, 300, 105, 90, 125, 90, 98) {}
    Hydreigon(const std::initializer_list<Move*> &moves) : Pokemon("Hydreigon", Type::DARK, Type::DRAGON, 50, 300, 105, 90, 125, 90, 98, moves) {}

    PokemonID getID() override {
        return PokemonID::HYDREIGON;
    }
};

struct Greninja : public Pokemon {
    Greninja() : Pokemon("Greninja", Type::WATER, Type::DARK, 50, 300, 95, 67, 103, 71, 122) {}
    Greninja(const std::initializer_list<Move*> &moves) : Pokemon("Greninja", Type::WATER, Type::DARK, 50, 300, 95, 67, 103, 71, 122, moves) {}

    PokemonID getID() override {
        return PokemonID::GRENINJA;
    }
};