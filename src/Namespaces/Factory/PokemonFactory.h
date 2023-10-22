//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Pokedex.h"

namespace PokemonFactory {
    inline Pokemon * getPokemon(const PokemonID id) {
        switch (id) {
            case VENASAUR:
                return new Venasaur;
            case CHARIZARD:
                return new Charizard;
            case PIKACHU:
                return new Pikachu;
            case LUCARIO:
                return new Lucario;
            case GRENINJA:
                return new Greninja;
            case VICTINI:
                return new Victini;
            case SNIVY:
                return new Snivy;
            case SERVINE:
                return new Servine;
            case SERPERIOR:
                return new Serperior;
            case TEPIG:
                return new Tepig;
            case PIGNITE:
                return new Pignite;
            case EMBOAR:
                return new Emboar;
            case OSHAWOTT:
                return new Oshawott;
            case DEWOTT:
                return new Dewott;
            case SAMUROTT:
                return new Samurott;
            case PATRAT:
                return new Patrat;
            case WATCHOG:
                return new Watchog;
            case LILLIPUP:
                return new Lillipup;
            case HERDIER:
                return new Herdier;
            case STOUTLAND:
                return new Stoutland;
            case PURRLOIN:
                return new Purrloin;
            case LIEPARD:
                return new Liepard;
            case PANSAGE:
                return new Pansage;
            case SIMISAGE:
                return new Simisage;
            case PANSEAR:
                return new Pansear;
            case SIMISEAR:
                return new Simisear;
            case PANPOUR:
                return new Panpour;
            case SIMIPOUR:
                return new Simipour;
            case MUNNA:
                return new Munna;
            case MUSHARNA:
                return new Musharna;
            case PIDOVE:
                return new Pidove;
            case TRANQUILL:
                return new Tranquill;
            case UNFEZANT:
                return new Unfezant;
            case BLITZLE:
                return new Blitzle;
            case ZEBSTRIKA:
                return new Zebstrika;
            case ROGGENROLA:
                return new Roggenrola;
            case BOLDORE:
                return new Boldore;
            case GIGALITH:
                return new Gigalith;
            case WOOBAT:
                return new Woobat;
            case SWOOBAT:
                return new Swoobat;
            case DRILBUR:
                return new Drilbur;
            case EXCADRILL:
                return new Excadrill;
            case AUDINO:
                return new Audino;
            case TIMBURR:
                return new Timburr;
            case GURDURR:
                return new Gurdurr;
            case CONKELDURR:
                return new Conkeldurr;
            case TYMPOLE:
                return new Tympole;
            case PALPITOAD:
                return new Palpitoad;
            case SEISMITOAD:
                return new Seismitoad;
            case THROH:
                return new Throh;
            case SAWK:
                return new Sawk;
            case SEWADDLE:
                break;
            case SWADLOON:
                break;
            case LEAVANNY:
                break;
            case VENIPEDE:
                break;
            case WHIRLIPEDE:
                break;
            case SCOLIPEDE:
                break;
            case COTTONEE:
                break;
            case WHIMSICOTT:
                break;
            case PETILIL:
                break;
            case LILLIGANT:
                break;
            case BASCULIN:
                break;
            case SANDILE:
                break;
            case KROKOROK:
                break;
            case KROOKODILE:
                break;
            case DARUMAKA:
                break;
            case DARMANITAN:
                break;
            case MARACTUS:
                break;
            case DWEBBLE:
                break;
            case CRUSTLE:
                break;
            case SCRAGGY:
                break;
            case SCRAFTY:
                break;
            case SIGILYPH:
                break;
            case YAMASK:
                break;
            case COFAGRIGUS:
                break;
            case TIRTOUGA:
                break;
            case CARRACOSTA:
                break;
            case ARCHEN:
                break;
            case ARCHEOPS:
                break;
            case TRUBBISH:
                break;
            case GARBODOR:
                break;
            case ZORUA:
                break;
            case ZOROARK:
                break;
            case MINCCINO:
                break;
            case CINCCINO:
                break;
            case GOTHITA:
                break;
            case GOTHORITA:
                break;
            case GOTHITELLE:
                break;
            case SOLOSIS:
                break;
            case DUOSION:
                break;
            case REUNICLUS:
                break;
            case DUCKLETT:
                break;
            case SWANNA:
                break;
            case VANILLITE:
                break;
            case VANILLISH:
                break;
            case VANILLUXE:
                break;
            case DEERLING:
                break;
            case SAWSBUCK:
                break;
            case EMOLGA:
                break;
            case KARRABLAST:
                break;
            case ESCAVALIER:
                break;
            case FOONGUS:
                break;
            case AMOONGUSS:
                break;
            case FRILLISH:
                break;
            case JELLICENT:
                break;
            case ALOMONOLA:
                break;
            case JOLTIK:
                break;
            case GALVANTULA:
                break;
            case FERROSEED:
                break;
            case FERROTHORN:
                break;
            case KLINK:
                break;
            case KLANG:
                break;
            case KLINKLANG:
                break;
            case TYNAMO:
                break;
            case EELEKTRIK:
                break;
            case ELEKTROSS:
                break;
            case ELGYEM:
                break;
            case BEHEEYEM:
                break;
            case LITWICK:
                break;
            case LAMPENT:
                break;
            case CHANDELURE:
                break;
            case AXEW:
                break;
            case FRAXURE:
                break;
            case HAXORUS:
                break;
            case CUBCHOO:
                break;
            case BEARTIC:
                break;
            case CRYOGONAL:
                break;
            case SHELMET:
                break;
            case ACCELGOR:
                break;
            case STUNFISH:
                break;
            case MIENFOO:
                break;
            case MINESHAO:
                break;
            case DRUDDIGON:
                break;
            case GOLETT:
                break;
            case GOLURK:
                break;
            case PAWNIARD:
                break;
            case BISHARP:
                break;
            case BOUFFALANT:
                break;
            case RUFFLET:
                break;
            case BRAVIARY:
                break;
            case VULLABY:
                break;
            case MANDIBUZZ:
                break;
            case HEATMOR:
                break;
            case DURANT:
                break;
            case DEINO:
                break;
            case ZWEILOUS:
                break;
            case HYDREIGON:
                return new Hydreigon;
            case LARVESTA:
                break;
            case VOLCARONA:
                break;
            case COBALION:
                break;
            case TERRAKION:
                break;
            case VIRIZION:
                break;
            case TORNADUS:
                break;
            case THUNDURUS:
                break;
            case RESHIRAM:
                break;
            case ZEKROM:
                break;
            case LANDORUS:
                break;
            case KYUREM:
                break;
            case KELDEO:
                break;
            case MELOETTA:
                break;
            case GENESECT:
                break;
            default:
                return nullptr;
        }

        //FIXME get rid of
        return nullptr;
    }
}
