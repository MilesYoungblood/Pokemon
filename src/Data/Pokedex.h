//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../Classes/Pokemon/Pokemon.h"

struct Venasaur : public Pokemon {
    Venasaur() : Pokemon("Venasaur", Type::GRASS, Type::POISON, 50, 80, 82, 83, 100, 100, 80, 45) {}
    Venasaur(const std::initializer_list<Move*> &moves) : Venasaur() {
        this->setMoves(moves);
    }

    PokemonID getID() override {
        return PokemonID::VENASAUR;
    }
};

struct Charizard : public Pokemon {
    Charizard() : Pokemon("Charizard", Type::FIRE, Type::FLYING, 50, 78, 84, 78, 109, 85, 100, 45) {}
    Charizard(const std::initializer_list<Move*> &moves) : Charizard() {
        this->setMoves(moves);
    }

    PokemonID getID() override {
        return PokemonID::CHARIZARD;
    }
};

struct Pikachu : public Pokemon {
    Pikachu() : Pokemon("Pikachu", Type::ELECTRIC, 50, 35, 55, 40, 50, 50, 90, 190) {}
    Pikachu(const std::initializer_list<Move*> &moves) : Pikachu() {
        this->setMoves(moves);
    }

    PokemonID getID() override {
        return PokemonID::PIKACHU;
    }
};

struct Lucario : public Pokemon {
    Lucario() : Pokemon("Lucario", Type::FIGHTING, Type::STEEL, 50, 70, 110, 70, 115, 70, 90, 45) {}
    Lucario(const std::initializer_list<Move*> &moves) : Lucario() {
        this->setMoves(moves);
    }

    PokemonID getID() override {
        return PokemonID::LUCARIO;
    }
};

struct Hydreigon : public Pokemon {
    Hydreigon() : Pokemon("Hydreigon", Type::DARK, Type::DRAGON, 50, 92, 105, 90, 125, 90, 98, 45) {}
    Hydreigon(const std::initializer_list<Move*> &moves) : Hydreigon() {
        this->setMoves(moves);
    }

    PokemonID getID() override {
        return PokemonID::HYDREIGON;
    }
};

struct Greninja : public Pokemon {
    Greninja() : Pokemon("Greninja", Type::WATER, Type::DARK, 50, 72, 95, 67, 103, 71, 122, 45) {}
    Greninja(const std::initializer_list<Move*> &moves) : Greninja() {
        this->setMoves(moves);
    }

    PokemonID getID() override {
        return PokemonID::GRENINJA;
    }
};