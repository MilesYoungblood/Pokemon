//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Pokedex.h"

namespace PokemonFactory {
    inline std::unique_ptr<Pokemon> getPokemon(const Pokemon::ID id) {
        switch (id) {
            case Pokemon::ID::VICTINI:
                return std::make_unique<Victini>();
            case Pokemon::ID::SNIVY:
                return std::make_unique<Snivy>();
            case Pokemon::ID::SERVINE:
                return std::make_unique<Servine>();
            case Pokemon::ID::SERPERIOR:
                return std::make_unique<Serperior>();
            case Pokemon::ID::TEPIG:
                return std::make_unique<Tepig>();
            case Pokemon::ID::PIGNITE:
                return std::make_unique<Pignite>();
            case Pokemon::ID::EMBOAR:
                return std::make_unique<Emboar>();
            case Pokemon::ID::OSHAWOTT:
                return std::make_unique<Oshawott>();
            case Pokemon::ID::DEWOTT:
                return std::make_unique<Dewott>();
            case Pokemon::ID::SAMUROTT:
                return std::make_unique<Samurott>();
            case Pokemon::ID::PATRAT:
                return std::make_unique<Patrat>();
            case Pokemon::ID::WATCHOG:
                return std::make_unique<Watchog>();
            case Pokemon::ID::LILLIPUP:
                return std::make_unique<Lillipup>();
            case Pokemon::ID::HERDIER:
                return std::make_unique<Herdier>();
            case Pokemon::ID::STOUTLAND:
                return std::make_unique<Stoutland>();
            case Pokemon::ID::PURRLOIN:
                return std::make_unique<Purrloin>();
            case Pokemon::ID::LIEPARD:
                return std::make_unique<Liepard>();
            case Pokemon::ID::PANSAGE:
                return std::make_unique<Pansage>();
            case Pokemon::ID::SIMISAGE:
                return std::make_unique<Simisage>();
            case Pokemon::ID::PANSEAR:
                return std::make_unique<Pansear>();
            case Pokemon::ID::SIMISEAR:
                return std::make_unique<Simisear>();
            case Pokemon::ID::PANPOUR:
                return std::make_unique<Panpour>();
            case Pokemon::ID::SIMIPOUR:
                return std::make_unique<Simipour>();
            case Pokemon::ID::MUNNA:
                return std::make_unique<Munna>();
            case Pokemon::ID::MUSHARNA:
                return std::make_unique<Musharna>();
            case Pokemon::ID::PIDOVE:
                return std::make_unique<Pidove>();
            case Pokemon::ID::TRANQUILL:
                return std::make_unique<Tranquill>();
            case Pokemon::ID::UNFEZANT:
                return std::make_unique<Unfezant>();
            case Pokemon::ID::BLITZLE:
                return std::make_unique<Blitzle>();
            case Pokemon::ID::ZEBSTRIKA:
                return std::make_unique<Zebstrika>();
            case Pokemon::ID::ROGGENROLA:
                return std::make_unique<Roggenrola>();
            case Pokemon::ID::BOLDORE:
                return std::make_unique<Boldore>();
            case Pokemon::ID::GIGALITH:
                return std::make_unique<Gigalith>();
            case Pokemon::ID::WOOBAT:
                return std::make_unique<Woobat>();
            case Pokemon::ID::SWOOBAT:
                return std::make_unique<Swoobat>();
            case Pokemon::ID::DRILBUR:
                return std::make_unique<Drilbur>();
            case Pokemon::ID::EXCADRILL:
                return std::make_unique<Excadrill>();
            case Pokemon::ID::AUDINO:
                return std::make_unique<Audino>();
            case Pokemon::ID::TIMBURR:
                return std::make_unique<Timburr>();
            case Pokemon::ID::GURDURR:
                return std::make_unique<Gurdurr>();
            case Pokemon::ID::CONKELDURR:
                return std::make_unique<Conkeldurr>();
            case Pokemon::ID::TYMPOLE:
                return std::make_unique<Tympole>();
            case Pokemon::ID::PALPITOAD:
                return std::make_unique<Palpitoad>();
            case Pokemon::ID::SEISMITOAD:
                return std::make_unique<Seismitoad>();
            case Pokemon::ID::THROH:
                return std::make_unique<Throh>();
            case Pokemon::ID::SAWK:
                return std::make_unique<Sawk>();
            case Pokemon::ID::SEWADDLE:
                break;
            case Pokemon::ID::SWADLOON:
                break;
            case Pokemon::ID::LEAVANNY:
                break;
            case Pokemon::ID::VENIPEDE:
                break;
            case Pokemon::ID::WHIRLIPEDE:
                break;
            case Pokemon::ID::SCOLIPEDE:
                break;
            case Pokemon::ID::COTTONEE:
                break;
            case Pokemon::ID::WHIMSICOTT:
                break;
            case Pokemon::ID::PETILIL:
                break;
            case Pokemon::ID::LILLIGANT:
                break;
            case Pokemon::ID::BASCULIN:
                break;
            case Pokemon::ID::SANDILE:
                break;
            case Pokemon::ID::KROKOROK:
                break;
            case Pokemon::ID::KROOKODILE:
                break;
            case Pokemon::ID::DARUMAKA:
                break;
            case Pokemon::ID::DARMANITAN:
                break;
            case Pokemon::ID::MARACTUS:
                break;
            case Pokemon::ID::DWEBBLE:
                break;
            case Pokemon::ID::CRUSTLE:
                break;
            case Pokemon::ID::SCRAGGY:
                break;
            case Pokemon::ID::SCRAFTY:
                break;
            case Pokemon::ID::SIGILYPH:
                break;
            case Pokemon::ID::YAMASK:
                break;
            case Pokemon::ID::COFAGRIGUS:
                break;
            case Pokemon::ID::TIRTOUGA:
                break;
            case Pokemon::ID::CARRACOSTA:
                break;
            case Pokemon::ID::ARCHEN:
                break;
            case Pokemon::ID::ARCHEOPS:
                break;
            case Pokemon::ID::TRUBBISH:
                break;
            case Pokemon::ID::GARBODOR:
                break;
            case Pokemon::ID::ZORUA:
                break;
            case Pokemon::ID::ZOROARK:
                break;
            case Pokemon::ID::MINCCINO:
                break;
            case Pokemon::ID::CINCCINO:
                break;
            case Pokemon::ID::GOTHITA:
                break;
            case Pokemon::ID::GOTHORITA:
                break;
            case Pokemon::ID::GOTHITELLE:
                break;
            case Pokemon::ID::SOLOSIS:
                break;
            case Pokemon::ID::DUOSION:
                break;
            case Pokemon::ID::REUNICLUS:
                break;
            case Pokemon::ID::DUCKLETT:
                break;
            case Pokemon::ID::SWANNA:
                break;
            case Pokemon::ID::VANILLITE:
                break;
            case Pokemon::ID::VANILLISH:
                break;
            case Pokemon::ID::VANILLUXE:
                break;
            case Pokemon::ID::DEERLING:
                break;
            case Pokemon::ID::SAWSBUCK:
                break;
            case Pokemon::ID::EMOLGA:
                break;
            case Pokemon::ID::KARRABLAST:
                break;
            case Pokemon::ID::ESCAVALIER:
                break;
            case Pokemon::ID::FOONGUS:
                break;
            case Pokemon::ID::AMOONGUSS:
                break;
            case Pokemon::ID::FRILLISH:
                break;
            case Pokemon::ID::JELLICENT:
                break;
            case Pokemon::ID::ALOMONOLA:
                break;
            case Pokemon::ID::JOLTIK:
                break;
            case Pokemon::ID::GALVANTULA:
                break;
            case Pokemon::ID::FERROSEED:
                break;
            case Pokemon::ID::FERROTHORN:
                break;
            case Pokemon::ID::KLINK:
                break;
            case Pokemon::ID::KLANG:
                break;
            case Pokemon::ID::KLINKLANG:
                break;
            case Pokemon::ID::TYNAMO:
                break;
            case Pokemon::ID::EELEKTRIK:
                break;
            case Pokemon::ID::ELEKTROSS:
                break;
            case Pokemon::ID::ELGYEM:
                break;
            case Pokemon::ID::BEHEEYEM:
                break;
            case Pokemon::ID::LITWICK:
                break;
            case Pokemon::ID::LAMPENT:
                break;
            case Pokemon::ID::CHANDELURE:
                break;
            case Pokemon::ID::AXEW:
                break;
            case Pokemon::ID::FRAXURE:
                break;
            case Pokemon::ID::HAXORUS:
                break;
            case Pokemon::ID::CUBCHOO:
                break;
            case Pokemon::ID::BEARTIC:
                break;
            case Pokemon::ID::CRYOGONAL:
                break;
            case Pokemon::ID::SHELMET:
                break;
            case Pokemon::ID::ACCELGOR:
                break;
            case Pokemon::ID::STUNFISH:
                break;
            case Pokemon::ID::MIENFOO:
                break;
            case Pokemon::ID::MINESHAO:
                break;
            case Pokemon::ID::DRUDDIGON:
                break;
            case Pokemon::ID::GOLETT:
                break;
            case Pokemon::ID::GOLURK:
                break;
            case Pokemon::ID::PAWNIARD:
                break;
            case Pokemon::ID::BISHARP:
                break;
            case Pokemon::ID::BOUFFALANT:
                break;
            case Pokemon::ID::RUFFLET:
                break;
            case Pokemon::ID::BRAVIARY:
                break;
            case Pokemon::ID::VULLABY:
                break;
            case Pokemon::ID::MANDIBUZZ:
                break;
            case Pokemon::ID::HEATMOR:
                break;
            case Pokemon::ID::DURANT:
                break;
            case Pokemon::ID::DEINO:
                break;
            case Pokemon::ID::ZWEILOUS:
                break;
            case Pokemon::ID::HYDREIGON:
                return std::make_unique<Hydreigon>();
            case Pokemon::ID::LARVESTA:
                break;
            case Pokemon::ID::VOLCARONA:
                break;
            case Pokemon::ID::COBALION:
                break;
            case Pokemon::ID::TERRAKION:
                break;
            case Pokemon::ID::VIRIZION:
                break;
            case Pokemon::ID::TORNADUS:
                break;
            case Pokemon::ID::THUNDURUS:
                break;
            case Pokemon::ID::RESHIRAM:
                break;
            case Pokemon::ID::ZEKROM:
                break;
            case Pokemon::ID::LANDORUS:
                break;
            case Pokemon::ID::KYUREM:
                break;
            case Pokemon::ID::KELDEO:
                break;
            case Pokemon::ID::MELOETTA:
                break;
            case Pokemon::ID::GENESECT:
                break;
            default:
                return nullptr;
        }
        return nullptr;
    }
}
