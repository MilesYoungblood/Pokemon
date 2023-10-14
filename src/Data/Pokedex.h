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

struct Victini : public Pokemon {
    Victini() : Pokemon("Victini", Type::PSYCHIC, Type::FIRE, 50, 100, 100, 100, 100, 100, 100, 3) {}

    PokemonID getID() override {
        return PokemonID::VICTINI;
    }
};

struct Snivy : public Pokemon {
    Snivy() : Pokemon("Snivy", Type::GRASS, 16, 45, 45, 55, 45, 55, 63, 45) {}

    PokemonID getID() override {
        return PokemonID::SNIVY;
    }
};

struct Servine : public Pokemon {
    Servine() : Pokemon("Servine", Type::GRASS, 35, 60, 60, 75, 60, 75, 83, 45) {}

    PokemonID getID() override {
        return PokemonID::SERVINE;
    }
};

struct Serperior : public Pokemon {
    Serperior() : Pokemon("Serperior", Type::GRASS, 50, 75, 75, 95, 75, 95, 113, 45) {}

    PokemonID getID() override {
        return PokemonID::SERPERIOR;
    }
};

struct Tepig : public Pokemon {
    Tepig() : Pokemon("Tepig", Type::FIRE, 16, 65, 63, 45, 45, 45, 45, 45) {}

    PokemonID getID() override {
        return PokemonID::TEPIG;
    }
};

struct Pignite : public Pokemon {
    Pignite() : Pokemon("Pignite", Type::FIRE, Type::FIGHTING, 35, 90, 93, 55, 70, 55, 55, 45) {}

    PokemonID getID() override {
        return PokemonID::PIGNITE;
    }
};

struct Emboar : public Pokemon {
    Emboar() : Pokemon("Emboar", Type::FIRE, Type::FIGHTING, 50, 110, 123, 65, 100, 65, 65, 45) {}

    PokemonID getID() override {
        return PokemonID::EMBOAR;
    }
};

struct Oshawott : public Pokemon {
    Oshawott() : Pokemon("Oshawott", Type::WATER, 16, 55, 55, 45, 63, 45, 45, 45) {}

    PokemonID getID() override {
        return PokemonID::OSHAWOTT;
    }
};

struct Dewott : public Pokemon {
    Dewott() : Pokemon("Dewott", Type::WATER, 35, 75, 75, 60, 83, 60, 60, 45) {}

    PokemonID getID() override {
        return PokemonID::DEWOTT;
    }
};

struct Samurott : public Pokemon {
    Samurott() : Pokemon("Samurott", Type::WATER, 50, 95, 100, 85, 108, 70, 70, 45) {}

    PokemonID getID() override {
        return PokemonID::SAMUROTT;
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