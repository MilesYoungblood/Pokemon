//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../Pokemon.h"

/*

struct PokemonData {
    const char *name;
    const Type type1;
    const Type type2;
    const int level;
    const int hp;
    const int attack;
    const int defense;
    const int spAttack;
    const int spDefense;
    const int speed;
    const int catchRate;
};

inline const std::unordered_map<Pokemon::Id, PokemonData> POKEMON_LOOKUP_TABLE{
        { Pokemon::Id::VICTINI,   { "Victini",   Type::PSYCHIC, Type::FIRE, 15, 100, 100, 100, 100, 100, 100, 3 }},
        { Pokemon::Id::SNIVY,     { "Snivy",     Type::GRASS,   Type::NONE, 1,  45,  45,  55,  45,  55,  63,  45 }},
        { Pokemon::Id::SERVINE,   { "Servine",   Type::GRASS,   Type::NONE, 17, 60,  60,  75,  60,  75,  83,  45 }},
        { Pokemon::Id::SERPERIOR, { "Serperior", Type::GRASS,   Type::NONE, 36, 75,  75,  95,  75,  95,  113, 45 }}
};

 */

struct Victini : public Pokemon {
    Victini() : Pokemon(15, 100, 100, 100, 100, 100, 100) {}

    Victini(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Victini";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::FIRE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::VICTINI;
    }
};

struct Snivy : public Pokemon {
    Snivy() : Pokemon(1, 45, 45, 55, 45, 55, 63) {}

    Snivy(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Snivy";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SNIVY;
    }
};

struct Servine : public Pokemon {
    Servine() : Pokemon(17, 60, 60, 75, 60, 75, 83) {}

    Servine(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Servine";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SERVINE;
    }
};

struct Serperior : public Pokemon {
    Serperior() : Pokemon(36, 75, 75, 95, 75, 95, 113) {}

    Serperior(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Serperior";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SERPERIOR;
    }
};

struct Tepig : public Pokemon {
    Tepig() : Pokemon(1, 65, 63, 45, 45, 45, 45) {}

    Tepig(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Tepig";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIRE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TEPIG;
    }
};

struct Pignite : public Pokemon {
    Pignite() : Pokemon(17, 90, 93, 55, 70, 55, 55) {}

    Pignite(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Pignite";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIRE : Type::FIGHTING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PIGNITE;
    }
};

struct Emboar : public Pokemon {
    Emboar() : Pokemon(36, 110, 123, 65, 100, 65, 65) {}

    Emboar(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Emboar";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIRE : Type::FIGHTING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::EMBOAR;
    }
};

struct Oshawott : public Pokemon {
    Oshawott() : Pokemon(1, 55, 55, 45, 63, 45, 45) {}

    Oshawott(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Oshawott";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::OSHAWOTT;
    }
};

struct Dewott : public Pokemon {
    Dewott() : Pokemon(17, 75, 75, 60, 83, 60, 60) {}

    Dewott(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Dewott";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DEWOTT;
    }
};

struct Samurott : public Pokemon {
    Samurott() : Pokemon(1, 95, 100, 85, 108, 70, 70) {}

    Samurott(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Samurott";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SAMUROTT;
    }
};

struct Patrat : public Pokemon {
    Patrat() : Pokemon(1, 45, 55, 39, 35, 39, 43) {}

    Patrat(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Patrat";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PATRAT;
    }
};

struct Watchog : public Pokemon {
    Watchog() : Pokemon(20, 60, 85, 69, 60, 69, 77) {}

    Watchog(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Watchog";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::WATCHOG;
    }
};

struct Lillipup : public Pokemon {
    Lillipup() : Pokemon(1, 45, 60, 45, 25, 45, 55) {}

    Lillipup(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Lillipup";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::LILLIPUP;
    }
};

struct Herdier : public Pokemon {
    Herdier() : Pokemon(16, 65, 80, 65, 35, 65, 60) {}

    Herdier(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Herdier";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::HERDIER;
    }
};

struct Stoutland : public Pokemon {
    Stoutland() : Pokemon(32, 85, 110, 90, 45, 90, 80) {}

    Stoutland(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Stoutland";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::STOUTLAND;
    }
};

struct Purrloin : public Pokemon {
    Purrloin() : Pokemon(1, 41, 50, 37, 50, 37, 66) {}

    Purrloin(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Purrloin";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PURRLOIN;
    }
};

struct Liepard : public Pokemon {
    Liepard() : Pokemon(20, 64, 88, 50, 88, 50, 106) {}

    Liepard(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Liepard";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::LIEPARD;
    }
};

struct Pansage : public Pokemon {
    Pansage() : Pokemon(1, 50, 53, 48, 53, 48, 64) {}

    Pansage(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Pansage";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PANSAGE;
    }
};

struct Simisage : public Pokemon {
    Simisage() : Pokemon(1, 75, 98, 63, 98, 63, 101) {}

    Simisage(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Simisage";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SIMISAGE;
    }
};

struct Pansear : public Pokemon {
    Pansear() : Pokemon(1, 50, 53, 48, 53, 48, 64) {}

    Pansear(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Pansear";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIRE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PANSEAR;
    }
};

struct Simisear : public Pokemon {
    Simisear() : Pokemon(1, 75, 98, 63, 98, 63, 101) {}

    Simisear(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Simisear";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIRE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SIMISEAR;
    }
};

struct Panpour : public Pokemon {
    Panpour() : Pokemon(1, 50, 53, 48, 53, 48, 64) {}

    Panpour(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Panpour";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PANPOUR;
    }
};

struct Simipour : public Pokemon {
    Simipour() : Pokemon(1, 75, 98, 63, 98, 63, 101) {}

    Simipour(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Simipour";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SIMIPOUR;
    }
};

struct Munna : public Pokemon {
    Munna() : Pokemon(1, 76, 25, 45, 67, 55, 24) {}

    Munna(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Munna";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::MUNNA;
    }
};

struct Musharna : public Pokemon {
    Musharna() : Pokemon(1, 116, 55, 85, 107, 95, 29) {}

    Musharna(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Musharna";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::MUSHARNA;
    }
};

struct Pidove : public Pokemon {
    Pidove() : Pokemon(1, 50, 55, 50, 36, 30, 43) {}

    Pidove(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Pidove";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PIDOVE;
    }
};

struct Tranquill : public Pokemon {
    Tranquill() : Pokemon(21, 62, 77, 62, 50, 42, 65) {}

    Tranquill(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Tranquill";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TRANQUILL;
    }
};

struct Unfezant : public Pokemon {
    Unfezant() : Pokemon(32, 80, 115, 80, 65, 55, 93) {}

    Unfezant(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Unfezant";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::UNFEZANT;
    }
};

struct Blitzle : public Pokemon {
    Blitzle() : Pokemon(1, 45, 60, 32, 50, 32, 76) {}

    Blitzle(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Blitzle";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::BLITZLE;
    }
};

struct Zebstrika : public Pokemon {
    Zebstrika() : Pokemon(27, 75, 100, 63, 80, 63, 116) {}

    Zebstrika(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Zebstrika";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ZEBSTRIKA;
    }
};

struct Roggenrola : public Pokemon {
    Roggenrola() : Pokemon(1, 55, 75, 85, 25, 25, 15) {}

    Roggenrola(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Roggenrola";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ROCK : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ROGGENROLA;
    }
};

struct Boldore : public Pokemon {
    Boldore() : Pokemon(25, 70, 105, 105, 50, 40, 20) {}

    Boldore(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Boldore";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ROCK : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::BOLDORE;
    }
};

struct Gigalith : public Pokemon {
    Gigalith() : Pokemon(25, 85, 135, 130, 60, 80, 25) {}

    Gigalith(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Gigalith";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ROCK : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GIGALITH;
    }
};

struct Woobat : public Pokemon {
    Woobat() : Pokemon(1, 65, 45, 43, 55, 43, 72) {}

    Woobat(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Woobat";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::WOOBAT;
    }
};

struct Swoobat : public Pokemon {
    Swoobat() : Pokemon(1, 67, 57, 55, 77, 55, 114) {}

    Swoobat(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Woobat";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SWOOBAT;
    }
};

struct Drilbur : public Pokemon {
    Drilbur() : Pokemon(1, 60, 85, 40, 30, 45, 68) {}

    Drilbur(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Drilbur";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GROUND : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DRILBUR;
    }
};

struct Excadrill : public Pokemon {
    Excadrill() : Pokemon(31, 110, 135, 60, 50, 65, 88) {}

    Excadrill(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Excadrill";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GROUND : Type::STEEL;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::EXCADRILL;
    }
};

struct Audino : public Pokemon {
    Audino() : Pokemon(1, 103, 60, 86, 60, 86, 50) {}

    Audino(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Audino";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::AUDINO;
    }
};

struct Timburr : public Pokemon {
    Timburr() : Pokemon(1, 75, 80, 55, 25, 35, 35) {}

    Timburr(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Timburr";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIGHTING : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 180;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TIMBURR;
    }
};

struct Gurdurr : public Pokemon {
    Gurdurr() : Pokemon(25, 85, 105, 85, 40, 50, 40) {}

    Gurdurr(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Gurdurr";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIGHTING : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GURDURR;
    }
};

struct Conkeldurr : public Pokemon {
    Conkeldurr() : Pokemon(25, 105, 140, 95, 55, 65, 45) {}

    Conkeldurr(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Conkeldurr";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIGHTING : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::CONKELDURR;
    }
};

struct Tympole : public Pokemon {
    Tympole() : Pokemon(1, 50, 50, 40, 50, 40, 64) {}

    Tympole(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Tympole";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TYMPOLE;
    }
};

struct Palpitoad : public Pokemon {
    Palpitoad() : Pokemon(25, 75, 65, 55, 65, 55, 69) {}

    Palpitoad(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Palpitoad";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::GROUND;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PALPITOAD;
    }
};

struct Seismitoad : public Pokemon {
    Seismitoad() : Pokemon(36, 105, 95, 75, 85, 75, 74) {}

    Seismitoad(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Seismitoad";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::GROUND;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SEISMITOAD;
    }

};

struct Throh : public Pokemon {
    Throh() : Pokemon(1, 120, 100, 85, 30, 85, 45) {}

    Throh(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Throh";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIGHTING : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::THROH;
    }
};

struct Sawk : public Pokemon {
    Sawk() : Pokemon(1, 75, 125, 75, 30, 75, 85) {}

    Sawk(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Sawk";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIGHTING : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SAWK;
    }
};

struct Hydreigon : public Pokemon {
    Hydreigon() : Pokemon(64, 92, 105, 90, 125, 90, 98) {}

    Hydreigon(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Hydreigon";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::DRAGON;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::HYDREIGON;
    }
};
