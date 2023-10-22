//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../Pokemon.h"

struct Venasaur : public Pokemon {
    Venasaur() : Pokemon("Venasaur", Type::GRASS, Type::POISON, 50, 80, 82, 83, 100, 100, 80, 45) {}
    Venasaur(const std::initializer_list<Move*> &moves) : Venasaur() {
        this->setMoves(moves);
    }

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::VENASAUR;
    }
};

struct Charizard : public Pokemon {
    Charizard() : Pokemon("Charizard", Type::FIRE, Type::FLYING, 50, 78, 84, 78, 109, 85, 100, 45) {}
    Charizard(const std::initializer_list<Move*> &moves) : Charizard() {
        this->setMoves(moves);
    }

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::CHARIZARD;
    }
};

struct Pikachu : public Pokemon {
    Pikachu() : Pokemon("Pikachu", Type::ELECTRIC, 50, 35, 55, 40, 50, 50, 90, 190) {}
    Pikachu(const std::initializer_list<Move*> &moves) : Pikachu() {
        this->setMoves(moves);
    }

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::PIKACHU;
    }
};

struct Lucario : public Pokemon {
    Lucario() : Pokemon("Lucario", Type::FIGHTING, Type::STEEL, 50, 70, 110, 70, 115, 70, 90, 45) {}
    Lucario(const std::initializer_list<Move*> &moves) : Lucario() {
        this->setMoves(moves);
    }

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::LUCARIO;
    }
};

struct Victini : public Pokemon {
    Victini() : Pokemon("Victini", Type::PSYCHIC, Type::FIRE, 15, 100, 100, 100, 100, 100, 100, 3) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::VICTINI;
    }
};

struct Snivy : public Pokemon {
    Snivy() : Pokemon("Snivy", Type::GRASS, 1, 45, 45, 55, 45, 55, 63, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::SNIVY;
    }
};

struct Servine : public Pokemon {
    Servine() : Pokemon("Servine", Type::GRASS, 17, 60, 60, 75, 60, 75, 83, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::SERVINE;
    }
};

struct Serperior : public Pokemon {
    Serperior() : Pokemon("Serperior", Type::GRASS, 36, 75, 75, 95, 75, 95, 113, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::SERPERIOR;
    }
};

struct Tepig : public Pokemon {
    Tepig() : Pokemon("Tepig", Type::FIRE, 1, 65, 63, 45, 45, 45, 45, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::TEPIG;
    }
};

struct Pignite : public Pokemon {
    Pignite() : Pokemon("Pignite", Type::FIRE, Type::FIGHTING, 17, 90, 93, 55, 70, 55, 55, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::PIGNITE;
    }
};

struct Emboar : public Pokemon {
    Emboar() : Pokemon("Emboar", Type::FIRE, Type::FIGHTING, 36, 110, 123, 65, 100, 65, 65, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::EMBOAR;
    }
};

struct Oshawott : public Pokemon {
    Oshawott() : Pokemon("Oshawott", Type::WATER, 1, 55, 55, 45, 63, 45, 45, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::OSHAWOTT;
    }
};

struct Dewott : public Pokemon {
    Dewott() : Pokemon("Dewott", Type::WATER, 17, 75, 75, 60, 83, 60, 60, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::DEWOTT;
    }
};

struct Samurott : public Pokemon {
    Samurott() : Pokemon("Samurott", Type::WATER, 1, 95, 100, 85, 108, 70, 70, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::SAMUROTT;
    }
};

struct Patrat : public Pokemon {
    Patrat() : Pokemon("Patrat", Type::NORMAL, 1, 45, 55, 39, 35, 39, 43, 255) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::PATRAT;
    }
};

struct Watchog : public Pokemon {
    Watchog() : Pokemon("Watchog", Type::NORMAL, 20, 60, 85, 69, 60, 69, 77, 255) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::WATCHOG;
    }
};

struct Lillipup : public Pokemon {
    Lillipup() : Pokemon("Lillipup", Type::NORMAL, 1, 45, 60, 45, 25, 45, 55, 255) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::LILLIPUP;
    }
};

struct Herdier : public Pokemon {
    Herdier() : Pokemon("Herdier", Type::NORMAL, 16, 65, 80, 65, 35, 65, 60, 120) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::HERDIER;
    }
};

struct Stoutland : public Pokemon {
    Stoutland() : Pokemon("Stoutland", Type::NORMAL, 32, 85, 110, 90, 45, 90, 80, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::STOUTLAND;
    }
};

struct Purrloin : public Pokemon {
    Purrloin() : Pokemon("Purrloin", Type::DARK, 1, 41, 50, 37, 50, 37, 66, 255) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::PURRLOIN;
    }
};

struct Liepard : public Pokemon {
    Liepard() : Pokemon("Liepard", Type::DARK, 20, 64, 88, 50, 88, 50, 106, 90) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::LIEPARD;
    }
};

struct Pansage : public Pokemon {
    Pansage() : Pokemon("Pansage", Type::GRASS, 1, 50, 53, 48, 53, 48, 64, 190) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::PANSAGE;
    }
};

struct Simisage : public Pokemon {
    Simisage() : Pokemon("Simisage", Type::GRASS, 1, 75, 98, 63, 98, 63, 101, 75) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::SIMISAGE;
    }
};

struct Pansear : public Pokemon {
    Pansear() : Pokemon("Pansear", Type::FIRE, 1, 50, 53, 48, 53, 48, 64, 190) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::PANSEAR;
    }
};

struct Simisear : public Pokemon {
    Simisear() : Pokemon("Simisear", Type::FIRE, 1, 75, 98, 63, 98, 63, 101, 75) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::SIMISEAR;
    }
};

struct Panpour : public Pokemon {
    Panpour() : Pokemon("Panpour", Type::WATER, 1, 50, 53, 48, 53, 48, 64, 190) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::PANPOUR;
    }
};

struct Simipour : public Pokemon {
    Simipour() : Pokemon("Simipour", Type::WATER, 1, 75, 98, 63, 98, 63, 101, 75) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::SIMIPOUR;
    }
};

struct Munna : public Pokemon {
    Munna() : Pokemon("Munna", Type::PSYCHIC, 1, 76, 25, 45, 67, 55, 24, 190) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::MUNNA;
    }
};

struct Musharna : public Pokemon {
    Musharna() : Pokemon("Musharna", Type::PSYCHIC, 1, 116, 55, 85, 107, 95, 29, 75) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::MUSHARNA;
    }
};

struct Pidove : public Pokemon {
    Pidove() : Pokemon("Pidove", Type::NORMAL, Type::FLYING, 1, 50, 55, 50, 36, 30, 43, 225) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::PIDOVE;
    }
};

struct Tranquill : public Pokemon {
    Tranquill() : Pokemon("Tranquill", Type::NORMAL, Type::FLYING, 21, 62, 77, 62, 50, 42, 65, 120) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::TRANQUILL;
    }
};

struct Unfezant : public Pokemon {
    Unfezant() : Pokemon("Unfezant", Type::NORMAL, Type::FLYING, 32, 80, 115, 80, 65, 55, 93, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::UNFEZANT;
    }
};

struct Blitzle : public Pokemon {
    Blitzle() : Pokemon("Blitzle", Type::ELECTRIC, 1, 45, 60, 32, 50, 32, 76, 190) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::BLITZLE;
    }
};

struct Zebstrika : public Pokemon {
    Zebstrika() : Pokemon("Zebstrika", Type::ELECTRIC, 27, 75, 100, 63, 80, 63, 116, 75) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::ZEBSTRIKA;
    }
};

struct Roggenrola : public Pokemon {
    Roggenrola() : Pokemon("Roggenrola", Type::ROCK, 1, 55, 75, 85, 25, 25, 15, 255) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::ROGGENROLA;
    }
};

struct Boldore : public Pokemon {
    Boldore() : Pokemon("Boldore", Type::ROCK, 25, 70, 105, 105, 50, 40, 20, 120) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::BOLDORE;
    }
};

struct Gigalith : public Pokemon {
    Gigalith() : Pokemon("Gigalith", Type::ROCK, 25, 85, 135, 130, 60, 80, 25, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::GIGALITH;
    }
};

struct Woobat : public Pokemon {
    Woobat() : Pokemon("Woobat", Type::PSYCHIC, Type::FLYING, 1, 65, 45, 43, 55, 43, 72, 190) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::WOOBAT;
    }
};

struct Swoobat : public Pokemon {
    Swoobat() : Pokemon("Swoobat", Type::PSYCHIC, Type::FLYING, 1, 67, 57, 55, 77, 55, 114, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::SWOOBAT;
    }
};

struct Drilbur : public Pokemon {
    Drilbur() : Pokemon("Drilbur", Type::GROUND, 1, 60, 85, 40, 30, 45, 68, 120) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::DRILBUR;
    }
};

struct Excadrill : public Pokemon {
    Excadrill() : Pokemon("Excadrill", Type::GROUND, Type::STEEL, 31, 110, 135, 60, 50, 65, 88, 60) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::EXCADRILL;
    }
};

struct Audino : public Pokemon {
    Audino() : Pokemon("Audino", Type::NORMAL, 1, 103, 60, 86, 60, 86, 50, 255) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::AUDINO;
    }
};

struct Timburr : public Pokemon {
    Timburr() : Pokemon("Timburr", Type::FIGHTING, 1, 75, 80, 55, 25, 35, 35, 180) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::TIMBURR;
    }
};

struct Gurdurr : public Pokemon {
    Gurdurr() : Pokemon("Gurdurr", Type::FIGHTING, 25, 85, 105, 85, 40, 50, 40, 90) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::GURDURR;
    }
};

struct Conkeldurr : public Pokemon {
    Conkeldurr() : Pokemon("Conkeldurr", Type::FIGHTING, 25, 105, 140, 95, 55, 65, 45, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::CONKELDURR;
    }
};

struct Tympole : public Pokemon {
    Tympole() : Pokemon("Tympole", Type::WATER, 1, 50, 50, 40, 50, 40, 64, 255) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::TYMPOLE;
    }
};

struct Palpitoad : public Pokemon {
    Palpitoad() : Pokemon("Palpitoad", Type::WATER, Type::GROUND, 25, 75, 65, 55, 65, 55, 69, 120) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::PALPITOAD;
    }
};

struct Seismitoad : public Pokemon {
    Seismitoad() : Pokemon("Seismitoad", Type::WATER, Type::GROUND, 36, 105, 95, 75, 85, 75, 74, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::SEISMITOAD;
    }

};

struct Throh : public Pokemon {
    Throh() : Pokemon("Throh", Type::FIGHTING, 1, 120, 100, 85, 30, 85, 45, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::THROH;
    }
};

struct Sawk : public Pokemon {
    Sawk() : Pokemon("Sawk", Type::FIGHTING, 1, 75, 125, 75, 30, 75, 85, 45) {}

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::SAWK;
    }
};

struct Hydreigon : public Pokemon {
    Hydreigon() : Pokemon("Hydreigon", Type::DARK, Type::DRAGON, 64, 92, 105, 90, 125, 90, 98, 45) {}
    Hydreigon(const std::initializer_list<Move*> &moves) : Hydreigon() {
        this->setMoves(moves);
    }

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::HYDREIGON;
    }
};

struct Greninja : public Pokemon {
    Greninja() : Pokemon("Greninja", Type::WATER, Type::DARK, 50, 72, 95, 67, 103, 71, 122, 45) {}
    Greninja(const std::initializer_list<Move*> &moves) : Greninja() {
        this->setMoves(moves);
    }

    [[nodiscard]] PokemonID getID() const override {
        return PokemonID::GRENINJA;
    }
};
