//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "Pokemon.h"

#include "DerivedClasses/Victini.h"
#include "DerivedClasses/Snivy.h"
#include "DerivedClasses/Servine.h"
#include "DerivedClasses/Serperior.h"
#include "DerivedClasses/Tepig.h"
#include "DerivedClasses/Pignite.h"
#include "DerivedClasses/Emboar.h"
#include "DerivedClasses/Oshawott.h"
#include "DerivedClasses/Dewott.h"
#include "DerivedClasses/Samurott.h"
#include "DerivedClasses/Patrat.h"
#include "DerivedClasses/Watchog.h"
#include "DerivedClasses/Lillipup.h"
#include "DerivedClasses/Herdier.h"
#include "DerivedClasses/Stoutland.h"
#include "DerivedClasses/Purrloin.h"
#include "DerivedClasses/Liepard.h"
#include "DerivedClasses/Pansage.h"
#include "DerivedClasses/Simisage.h"
#include "DerivedClasses/Pansear.h"
#include "DerivedClasses/Simisear.h"
#include "DerivedClasses/Panpour.h"
#include "DerivedClasses/Simipour.h"
#include "DerivedClasses/Munna.h"
#include "DerivedClasses/Musharna.h"
#include "DerivedClasses/Pidove.h"
#include "DerivedClasses/Tranquill.h"
#include "DerivedClasses/Unfezant.h"
#include "DerivedClasses/Blitzle.h"
#include "DerivedClasses/Zebstrika.h"
#include "DerivedClasses/Roggenrola.h"
#include "DerivedClasses/Boldore.h"
#include "DerivedClasses/Gigalith.h"
#include "DerivedClasses/Woobat.h"
#include "DerivedClasses/Swoobat.h"
#include "DerivedClasses/Drilbur.h"
#include "DerivedClasses/Excadrill.h"
#include "DerivedClasses/Audino.h"
#include "DerivedClasses/Timburr.h"
#include "DerivedClasses/Gurdurr.h"
#include "DerivedClasses/Conkeldurr.h"
#include "DerivedClasses/Tympole.h"
#include "DerivedClasses/Palpitoad.h"
#include "DerivedClasses/Seismitoad.h"
#include "DerivedClasses/Throh.h"
#include "DerivedClasses/Sawk.h"
#include "DerivedClasses/Sewaddle.h"
#include "DerivedClasses/Swadloon.h"
#include "DerivedClasses/Leavanny.h"
#include "DerivedClasses/Venipede.h"
#include "DerivedClasses/Whirlipede.h"
#include "DerivedClasses/Scolipede.h"
#include "DerivedClasses/Cottonee.h"
#include "DerivedClasses/Whimsicott.h"
#include "DerivedClasses/Petilil.h"
#include "DerivedClasses/Lilligant.h"
#include "DerivedClasses/Basculin.h"
#include "DerivedClasses/Sandile.h"
#include "DerivedClasses/Krokorok.h"
#include "DerivedClasses/Krookodile.h"
#include "DerivedClasses/Darumaka.h"
#include "DerivedClasses/Darmanitan.h"
#include "DerivedClasses/Maractus.h"
#include "DerivedClasses/Dwebble.h"
#include "DerivedClasses/Crustle.h"
#include "DerivedClasses/Scraggy.h"
#include "DerivedClasses/Scrafty.h"
#include "DerivedClasses/Sigilyph.h"
#include "DerivedClasses/Yamask.h"
#include "DerivedClasses/Cofagrigus.h"
#include "DerivedClasses/Tirtouga.h"
#include "DerivedClasses/Carracosta.h"

struct Archen : public Pokemon {
    Archen() : Pokemon(1, 55, 112, 45, 74, 45, 70) {}

    Archen(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Archen";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ROCK : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ARCHEN;
    }
};

struct Archeops : public Pokemon {
    Archeops() : Pokemon(37, 75, 140, 65, 112, 65, 110) {}

    Archeops(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Archeops";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ROCK : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ARCHEOPS;
    }
};

struct Trubbish : public Pokemon {
    Trubbish() : Pokemon(1, 50, 50, 62, 40, 62, 65) {}

    Trubbish(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Trubbish";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::POISON : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TRUBBISH;
    }
};

struct Garbodor : public Pokemon {
    Garbodor() : Pokemon(36, 80, 95, 82, 60, 82, 75) {}

    Garbodor(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Garbodor";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::POISON : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GARBODOR;
    }
};

struct Zorua : public Pokemon {
    Zorua() : Pokemon(1, 40, 65, 40, 80, 40, 65) {}

    Zorua(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Zorua";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ZORUA;
    }
};

struct Zoroark : public Pokemon {
    Zoroark() : Pokemon(30, 60, 105, 60, 120, 60, 105) {}

    Zoroark(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Zoroark";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ZOROARK;
    }
};

struct Minccino : public Pokemon {
    Minccino() : Pokemon(1, 55, 50, 40, 40, 40, 75) {}

    Minccino(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Minccino";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::MINCCINO;
    }
};

struct Cinccino : public Pokemon {
    Cinccino() : Pokemon(1, 75, 95, 60, 65, 60, 115) {}

    Cinccino(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Cinccino";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::CINCCINO;
    }
};

struct Gothita : public Pokemon {
    Gothita() : Pokemon(1, 45, 30, 50, 55, 65, 45) {}

    Gothita(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Gothita";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 200;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GOTHITA;
    }
};

struct Gothorita : public Pokemon {
    Gothorita() : Pokemon(32, 60, 45, 70, 75, 85, 55) {}

    Gothorita(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Gothorita";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 100;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GOTHORITA;
    }
};

struct Gothitelle : public Pokemon {
    Gothitelle() : Pokemon(41, 70, 55, 95, 95, 110, 65) {}

    Gothitelle(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Gothitelle";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 50;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GOTHITELLE;
    }
};

struct Solosis : public Pokemon {
    Solosis() : Pokemon(1, 45, 30, 40, 105, 50, 20) {}

    Solosis(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Solosis";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 200;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SOLOSIS;
    }
};

struct Duosion : public Pokemon {
    Duosion() : Pokemon(32, 65, 40, 50, 125, 60, 30) {}

    Duosion(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Duosion";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 100;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DUOSION;
    }
};

struct Reuniclus : public Pokemon {
    Reuniclus() : Pokemon(41, 110, 65, 75, 125, 85, 30) {}

    Reuniclus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Reuniclus";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 50;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::REUNICLUS;
    }
};

struct Ducklett : public Pokemon {
    Ducklett() : Pokemon(1, 62, 44, 50, 44, 50, 55) {}

    Ducklett(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Ducklett";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DUCKLETT;
    }
};

struct Swanna : public Pokemon {
    Swanna() : Pokemon(35, 75, 87, 63, 87, 63, 98) {}

    Swanna(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Swanna";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SWANNA;
    }
};

struct Vanillite : public Pokemon {
    Vanillite() : Pokemon(1, 36, 50, 50, 65, 60, 44) {}

    Vanillite(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Vanillite";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ICE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::VANILLITE;
    }
};

struct Vanillish : public Pokemon {
    Vanillish() : Pokemon(35, 51, 65, 65, 80, 75, 59) {}

    Vanillish(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Vanillish";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ICE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::VANILLISH;
    }
};

struct Vanilluxe : public Pokemon {
    Vanilluxe() : Pokemon(47, 71, 95, 85, 110, 95, 79) {}

    Vanilluxe(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Vanilluxe";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ICE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::VANILLUXE;
    }
};

struct Deerling : public Pokemon {
    Deerling() : Pokemon(1, 60, 60, 50, 40, 50, 75) {}

    Deerling(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Deerling";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::GRASS;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DEERLING;
    }
};

struct Sawsbuck : public Pokemon {
    Sawsbuck() : Pokemon(34, 80, 100, 70, 60, 70, 95) {}

    Sawsbuck(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Sawsbuck";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::GRASS;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SAWSBUCK;
    }
};

struct Emolga : public Pokemon {
    Emolga() : Pokemon(1, 55, 75, 60, 75, 60, 103) {}

    Emolga(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Emolga";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 200;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::EMOLGA;
    }
};

struct Karrablast : public Pokemon {
    Karrablast() : Pokemon(1, 50, 75, 45, 40, 45, 60) {}

    Karrablast(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Karrablast";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 200;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::KARRABLAST;
    }
};

struct Escavalier : public Pokemon {
    Escavalier() : Pokemon(1, 70, 135, 105, 60, 105, 20) {}

    Escavalier(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Escavalier";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::STEEL;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ESCAVALIER;
    }
};

struct Foongus : public Pokemon {
    Foongus() : Pokemon(1, 69, 55, 45, 55, 55, 15) {}

    Foongus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Foongus";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::POISON;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::FOONGUS;
    }
};

struct Amoonguss : public Pokemon {
    Amoonguss() : Pokemon(39, 114, 85, 70, 85, 80, 30) {}

    Amoonguss(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Amoonguss";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::POISON;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::AMOONGUSS;
    }
};

struct Frillish : public Pokemon {
    Frillish() : Pokemon(1, 55, 40, 50, 65, 85, 40) {}

    Frillish(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Frillish";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::GHOST;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::FRILLISH;
    }
};

struct Jellicent : public Pokemon {
    Jellicent() : Pokemon(40, 100, 60, 70, 85, 105, 60) {}

    Jellicent(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Jellicent";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::GHOST;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::JELLICENT;
    }
};

struct Alomomola : public Pokemon {
    Alomomola() : Pokemon(1, 165, 75, 80, 40, 45, 65) {}

    Alomomola(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Alomomola";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ALOMOMOLA;
    }
};

struct Joltik : public Pokemon {
    Joltik() : Pokemon(1, 50, 47, 50, 57, 50, 65) {}

    Joltik(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Joltik";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::ELECTRIC;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::JOLTIK;
    }
};

struct Galvantula : public Pokemon {
    Galvantula() : Pokemon(36, 70, 77, 60, 97, 60, 108) {}

    Galvantula(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Galvantula";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::ELECTRIC;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GALVANTULA;
    }
};

struct Ferroseed : public Pokemon {
    Ferroseed() : Pokemon(1, 44, 50, 91, 24, 86, 10) {}

    Ferroseed(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Ferroseed";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::STEEL;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::FERROSEED;
    }
};

struct Ferrothorn : public Pokemon {
    Ferrothorn() : Pokemon(40, 74, 94, 131, 54, 116, 20) {}

    Ferrothorn(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Ferrothorn";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::STEEL;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::FERROTHORN;
    }
};

struct Klink : public Pokemon {
    Klink() : Pokemon(1, 40, 55, 70, 45, 60, 30) {}

    Klink(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Klink";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::STEEL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 130;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::KLINK;
    }
};

struct Klang : public Pokemon {
    Klang() : Pokemon(38, 60, 80, 95, 70, 85, 50) {}

    Klang(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Klang";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::STEEL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::KLANG;
    }
};

struct Klinklang : public Pokemon {
    Klinklang() : Pokemon(49, 60, 100, 115, 70, 85, 90) {}

    Klinklang(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Klinklang";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::STEEL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 30;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::KLINKLANG;
    }
};

struct Tynamo : public Pokemon {
    Tynamo() : Pokemon(1, 35, 55, 40, 45, 40, 60) {}

    Tynamo(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Tynamo";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TYNAMO;
    }
};

struct Eelektrik : public Pokemon {
    Eelektrik() : Pokemon(39, 65, 85, 70, 75, 70, 40) {}

    Eelektrik(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Eelektrik";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::EELEKTRIK;
    }
};

struct Eelektross : public Pokemon {
    Eelektross() : Pokemon(39, 85, 115, 80, 105, 80, 50) {}

    Eelektross(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Eelektross";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 30;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::EELEKTROSS;
    }
};

struct Elgyem : public Pokemon {
    Elgyem() : Pokemon(1, 55, 55, 55, 85, 55, 30) {}

    Elgyem(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Elgyem";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 255;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ELGYEM;
    }
};

struct Beheeyem : public Pokemon {
    Beheeyem() : Pokemon(42, 75, 75, 75, 125, 95, 40) {}

    Beheeyem(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Beheeyem";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::PSYCHIC : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::BEHEEYEM;
    }
};

struct Litwick : public Pokemon {
    Litwick() : Pokemon(1, 50, 30, 55, 65, 55, 20) {}

    Litwick(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Litwick";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GHOST : Type::FIRE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::LITWICK;
    }
};

struct Lampent : public Pokemon {
    Lampent() : Pokemon(41, 60, 40, 60, 95, 60, 55) {}

    Lampent(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Lampent";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GHOST : Type::FIRE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::LAMPENT;
    }
};

struct Chandelure : public Pokemon {
    Chandelure() : Pokemon(41, 60, 55, 90, 145, 90, 80) {}

    Chandelure(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Chandelure";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GHOST : Type::FIRE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::CHANDELURE;
    }
};

struct Axew : public Pokemon {
    Axew() : Pokemon(1, 46, 87, 60, 30, 40, 57) {}

    Axew(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Axew";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DRAGON : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::AXEW;
    }
};

struct Fraxure : public Pokemon {
    Fraxure() : Pokemon(38, 66, 117, 70, 40, 50, 67) {}

    Fraxure(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Fraxure";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DRAGON : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::FRAXURE;
    }
};

struct Haxorus : public Pokemon {
    Haxorus() : Pokemon(48, 76, 147, 90, 60, 70, 97) {}

    Haxorus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Haxorus";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DRAGON : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::HAXORUS;
    }
};

struct Cubchoo : public Pokemon {
    Cubchoo() : Pokemon(1, 55, 70, 40, 60, 40, 40) {}

    Cubchoo(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Cubchoo";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ICE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::CUBCHOO;
    }
};

struct Beartic : public Pokemon {
    Beartic() : Pokemon(37, 95, 130, 80, 70, 80, 50) {}

    Beartic(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Beartic";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ICE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::BEARTIC;
    }
};

struct Cryogonal : public Pokemon {
    Cryogonal() : Pokemon(1, 80, 50, 50, 95, 135, 105) {}

    Cryogonal(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Cryogonal";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ICE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 25;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::CRYOGONAL;
    }
};

struct Shelmet : public Pokemon {
    Shelmet() : Pokemon(1, 50, 40, 85, 40, 65, 25) {}

    Shelmet(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Shelmet";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 200;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::SHELMET;
    }
};

struct Accelgor : public Pokemon {
    Accelgor() : Pokemon(1, 80, 70, 40, 100, 60, 145) {}

    Accelgor(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Accelgor";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ACCELGOR;
    }
};

struct Stunfisk : public Pokemon {
    Stunfisk() : Pokemon(1, 109, 66, 84, 81, 99, 32) {}

    Stunfisk(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Stunfisk";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GROUND : Type::ELECTRIC;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 75;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::STUNFISK;
    }
};

struct Mienfoo : public Pokemon {
    Mienfoo() : Pokemon(1, 45, 85, 50, 55, 50, 65) {}

    Mienfoo(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Mienfoo";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIGHTING : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 180;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::MIENFOO;
    }
};

struct Mienshao : public Pokemon {
    Mienshao() : Pokemon(50, 65, 125, 60, 95, 60, 105) {}

    Mienshao(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Mienshao";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIGHTING : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::MIENSHAO;
    }
};

struct Druddigon : public Pokemon {
    Druddigon() : Pokemon(1, 77, 120, 90, 60, 90, 48) {}

    Druddigon(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Druddigon";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DRAGON : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DRUDDIGON;
    }
};

struct Golett : public Pokemon {
    Golett() : Pokemon(1, 59, 74, 50, 35, 50, 35) {}

    Golett(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Golett";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GROUND : Type::GHOST;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GOLETT;
    }
};

struct Golurk : public Pokemon {
    Golurk() : Pokemon(43, 89, 124, 80, 55, 80, 55) {}

    Golurk(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Golurk";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GROUND : Type::GHOST;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GOLURK;
    }
};

struct Pawniard : public Pokemon {
    Pawniard() : Pokemon(1, 45, 85, 70, 40, 40, 60) {}

    Pawniard(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Pawniard";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::STEEL;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 120;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::PAWNIARD;
    }
};

struct Bisharp : public Pokemon {
    Bisharp() : Pokemon(52, 65, 125, 100, 60, 70, 70) {}

    Bisharp(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Bisharp";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::STEEL;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::BISHARP;
    }
};

struct Bouffalant : public Pokemon {
    Bouffalant() : Pokemon(1, 95, 110, 95, 40, 95, 55) {}

    Bouffalant(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Bouffalant";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::BOUFFALANT;
    }
};

struct Rufflet : public Pokemon {
    Rufflet() : Pokemon(1, 70, 83, 50, 37, 50, 60) {}

    Rufflet(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Rufflet";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::RUFFLET;
    }
};

struct Braviary : public Pokemon {
    Braviary() : Pokemon(54, 100, 123, 75, 57, 75, 80) {}

    Braviary(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Braviary";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::BRAVIARY;
    }
};

struct Vullaby : public Pokemon {
    Vullaby() : Pokemon(1, 70, 55, 75, 45, 65, 60) {}

    Vullaby(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Vullaby";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 190;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::VULLABY;
    }
};

struct Mandibuzz : public Pokemon {
    Mandibuzz() : Pokemon(54, 110, 65, 105, 55, 95, 80) {}

    Mandibuzz(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Mandibuzz";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 60;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::MANDIBUZZ;
    }
};

struct Heatmor : public Pokemon {
    Heatmor() : Pokemon(1, 85, 97, 66, 105, 66, 65) {}

    Heatmor(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Heatmor";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FIRE : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::HEATMOR;
    }
};

struct Durant : public Pokemon {
    Durant() : Pokemon(1, 58, 109, 112, 48, 48, 109) {}

    Durant(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Durant";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::STEEL;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 90;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DURANT;
    }
};

struct Deino : public Pokemon {
    Deino() : Pokemon(1, 52, 65, 50, 45, 50, 38) {}

    Deino(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Deino";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::DRAGON;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::DEINO;
    }
};

struct Zweilous : public Pokemon {
    Zweilous() : Pokemon(50, 52, 65, 50, 45, 60, 38) {}

    Zweilous(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Zweilous";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DARK : Type::DRAGON;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ZWEILOUS;
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

struct Larvesta : public Pokemon {
    Larvesta() : Pokemon(1, 55, 85, 55, 50, 55, 60) {}

    Larvesta(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Larvesta";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::FIRE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 45;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::LARVESTA;
    }
};

struct Volcarona : public Pokemon {
    Volcarona() : Pokemon(59, 85, 60, 65, 135, 105, 100) {}

    Volcarona(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Volcarona";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::FIRE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 15;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::VOLCARONA;
    }
};

struct Cobalion : public Pokemon {
    Cobalion() : Pokemon(42, 91, 90, 129, 90, 72, 108) {}

    Cobalion(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Cobalion";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::STEEL : Type::FIGHTING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::COBALION;
    }
};

struct Terrakion : public Pokemon {
    Terrakion() : Pokemon(42, 91, 129, 90, 72, 90, 108) {}

    Terrakion(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Terrakion";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ROCK : Type::FIGHTING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TERRAKION;
    }
};

struct Virizion : public Pokemon {
    Virizion() : Pokemon(42, 91, 90, 72, 90, 129, 108) {}

    Virizion(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Virizion";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GRASS : Type::FIGHTING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::VIRIZION;
    }
};

struct Tornadus : public Pokemon {
    Tornadus() : Pokemon(40, 79, 115, 70, 125, 80, 111) {}

    Tornadus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Tornadus";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::FLYING : Type::NONE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::TORNADUS;
    }
};

struct Thundurus : public Pokemon {
    Thundurus() : Pokemon(40, 79, 115, 70, 125, 80, 111) {}

    Thundurus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Thundurus";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::ELECTRIC : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::THUNDURUS;
    }
};

struct Reshiram : public Pokemon {
    Reshiram() : Pokemon(50, 100, 120, 100, 150, 120, 90) {}

    Reshiram(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Reshiram";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DRAGON : Type::FIRE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::RESHIRAM;
    }
};

struct Zekrom : public Pokemon {
    Zekrom() : Pokemon(50, 100, 150, 120, 120, 100, 90) {}

    Zekrom(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Zekrom";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DRAGON : Type::ELECTRIC;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::ZEKROM;
    }
};

struct Landorus : public Pokemon {
    Landorus() : Pokemon(70, 89, 125, 90, 115, 80, 101) {}

    Landorus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Landorus";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::GROUND : Type::FLYING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::LANDORUS;
    }
};

struct Kyurem : public Pokemon {
    Kyurem() : Pokemon(75, 125, 130, 90, 130, 90, 95) {}

    Kyurem(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Kyurem";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::DRAGON : Type::ICE;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::KYUREM;
    }
};

struct Keldeo : public Pokemon {
    Keldeo() : Pokemon(15, 91, 72, 90, 129, 90, 108) {}

    Keldeo(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Keldeo";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::WATER : Type::FIGHTING;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::KELDEO;
    }
};

struct Meloetta : public Pokemon {
    Meloetta() : Pokemon(15, 100, 77, 77, 128, 128, 90) {}

    Meloetta(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Meloetta";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::NORMAL : Type::PSYCHIC;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::MELOETTA;
    }
};

struct Genesect : public Pokemon {
    Genesect() : Pokemon(15, 71, 120, 95, 120, 95, 99) {}

    Genesect(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
            : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

    [[nodiscard]] std::string getName() const override {
        return "Genesect";
    }

    [[nodiscard]] Type getType(bool type1) const override {
        return type1 ? Type::BUG : Type::STEEL;
    }

    [[nodiscard]] int getCatchRate() const override {
        return 3;
    }

    [[nodiscard]] Pokemon::Id getId() const override {
        return Pokemon::Id::GENESECT;
    }
};
