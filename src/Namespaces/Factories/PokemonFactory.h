//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Pokedex.h"

namespace PokemonFactory {
    inline std::unique_ptr<Pokemon> getPokemon(const PokemonID id) {
        switch (id) {
            case VENASAUR:
                return std::make_unique<Venasaur>();
            case CHARIZARD:
                return std::make_unique<Charizard>();
            case PIKACHU:
                return std::make_unique<Pikachu>();
            case LUCARIO:
                return std::make_unique<Lucario>();
            case GRENINJA:
                return std::make_unique<Greninja>();
            case VICTINI:
                return std::make_unique<Victini>();
            case SNIVY:
                return std::make_unique<Snivy>();
            case SERVINE:
                return std::make_unique<Servine>();
            case SERPERIOR:
                return std::make_unique<Serperior>();
            case TEPIG:
                return std::make_unique<Tepig>();
            case PIGNITE:
                return std::make_unique<Pignite>();
            case EMBOAR:
                return std::make_unique<Emboar>();
            case OSHAWOTT:
                return std::make_unique<Oshawott>();
            case DEWOTT:
                return std::make_unique<Dewott>();
            case SAMUROTT:
                return std::make_unique<Samurott>();
            case PATRAT:
                return std::make_unique<Patrat>();
            case WATCHOG:
                return std::make_unique<Watchog>();
            case LILLIPUP:
                return std::make_unique<Lillipup>();
            case HERDIER:
                return std::make_unique<Herdier>();
            case STOUTLAND:
                return std::make_unique<Stoutland>();
            case PURRLOIN:
                return std::make_unique<Purrloin>();
            case LIEPARD:
                return std::make_unique<Liepard>();
            case PANSAGE:
                return std::make_unique<Pansage>();
            case SIMISAGE:
                return std::make_unique<Simisage>();
            case PANSEAR:
                return std::make_unique<Pansear>();
            case SIMISEAR:
                return std::make_unique<Simisear>();
            case PANPOUR:
                return std::make_unique<Panpour>();
            case SIMIPOUR:
                return std::make_unique<Simipour>();
            case MUNNA:
                return std::make_unique<Munna>();
            case MUSHARNA:
                return std::make_unique<Musharna>();
            case PIDOVE:
                return std::make_unique<Pidove>();
            case TRANQUILL:
                return std::make_unique<Tranquill>();
            case UNFEZANT:
                return std::make_unique<Unfezant>();
            case BLITZLE:
                return std::make_unique<Blitzle>();
            case ZEBSTRIKA:
                return std::make_unique<Zebstrika>();
            case ROGGENROLA:
                return std::make_unique<Roggenrola>();
            case BOLDORE:
                return std::make_unique<Boldore>();
            case GIGALITH:
                return std::make_unique<Gigalith>();
            case WOOBAT:
                return std::make_unique<Woobat>();
            case SWOOBAT:
                return std::make_unique<Swoobat>();
            case DRILBUR:
                return std::make_unique<Drilbur>();
            case EXCADRILL:
                return std::make_unique<Excadrill>();
            case AUDINO:
                return std::make_unique<Audino>();
            case TIMBURR:
                return std::make_unique<Timburr>();
            case GURDURR:
                return std::make_unique<Gurdurr>();
            case CONKELDURR:
                return std::make_unique<Conkeldurr>();
            case TYMPOLE:
                return std::make_unique<Tympole>();
            case PALPITOAD:
                return std::make_unique<Palpitoad>();
            case SEISMITOAD:
                return std::make_unique<Seismitoad>();
            case THROH:
                return std::make_unique<Throh>();
            case SAWK:
                return std::make_unique<Sawk>();
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
                return std::make_unique<Hydreigon>();
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
