//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../Data/Pokedex.h"

namespace PokemonFactory {
    inline Pokemon *getPokemon(PokemonID id) {
        switch (id) {
            case VENASAUR:
                return new Venasaur();
            case CHARIZARD:
                return new Charizard();
            case PIKACHU:
                return new Pikachu();
            case LUCARIO:
                return new Lucario();
            case GRENINJA:
                return new Greninja();
            case VICTINI:
                return new Victini();
            case SNIVY:
                return new Snivy();
            case SERVINE:
                return new Servine();
            case SERPERIOR:
                return new Serperior();
            case TEPIG:
                return new Tepig();
            case PIGNITE:
                return new Pignite();
            case EMBOAR:
                return new Emboar();
            case OSHAWOTT:
                return new Oshawott();
            case DEWOTT:
                return new Dewott();
            case SAMUROTT:
                return new Samurott();
            case PATRAT:
                break;
            case WATCHOG:
                break;
            case LILLIPUP:
                break;
            case HERDIER:
                break;
            case STOUTLAND:
                break;
            case PURRLOIN:
                break;
            case LIEPARD:
                break;
            case PANSAGE:
                break;
            case SIMISAGE:
                break;
            case PANSEAR:
                break;
            case SIMISEAR:
                break;
            case PANPOUR:
                break;
            case SIMIPOUR:
                break;
            case MUNNA:
                break;
            case MUSHARNA:
                break;
            case PIDOVE:
                break;
            case TRANQUILL:
                break;
            case UNFEZANT:
                break;
            case BLITZLE:
                break;
            case ZEBSTRIKA:
                break;
            case ROGGENROLA:
                break;
            case BOLDORE:
                break;
            case GIGALITH:
                break;
            case WOOBAT:
                break;
            case SWOOBAT:
                break;
            case DRILBUR:
                break;
            case EXCADRILL:
                break;
            case AUDINO:
                break;
            case TIMBURR:
                break;
            case GURDURR:
                break;
            case CONKELDURR:
                break;
            case TYMPOLE:
                break;
            case PALPITOAD:
                break;
            case SEISMITOAD:
                break;
            case THROH:
                break;
            case SAWK:
                break;
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
            case GORORITA:
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
            case VANINILLUXE:
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
            case ZEWILOUS:
                break;
            case HYDREIGON:
                return new Hydreigon();
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
    }
}
