//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../Classes/Entity/DerivedClasses/Pokemon/DerivedClasses/Pokedex.h"

namespace PokemonFactory {
    inline std::unique_ptr<Pokemon> getPokemon(Pokemon::Id id) {
        switch (id) {
            case Pokemon::Id::VICTINI:
                return std::make_unique<Victini>();
            case Pokemon::Id::SNIVY:
                return std::make_unique<Snivy>();
            case Pokemon::Id::SERVINE:
                return std::make_unique<Servine>();
            case Pokemon::Id::SERPERIOR:
                return std::make_unique<Serperior>();
            case Pokemon::Id::TEPIG:
                return std::make_unique<Tepig>();
            case Pokemon::Id::PIGNITE:
                return std::make_unique<Pignite>();
            case Pokemon::Id::EMBOAR:
                return std::make_unique<Emboar>();
            case Pokemon::Id::OSHAWOTT:
                return std::make_unique<Oshawott>();
            case Pokemon::Id::DEWOTT:
                return std::make_unique<Dewott>();
            case Pokemon::Id::SAMUROTT:
                return std::make_unique<Samurott>();
            case Pokemon::Id::PATRAT:
                return std::make_unique<Patrat>();
            case Pokemon::Id::WATCHOG:
                return std::make_unique<Watchog>();
            case Pokemon::Id::LILLIPUP:
                return std::make_unique<Lillipup>();
            case Pokemon::Id::HERDIER:
                return std::make_unique<Herdier>();
            case Pokemon::Id::STOUTLAND:
                return std::make_unique<Stoutland>();
            case Pokemon::Id::PURRLOIN:
                return std::make_unique<Purrloin>();
            case Pokemon::Id::LIEPARD:
                return std::make_unique<Liepard>();
            case Pokemon::Id::PANSAGE:
                return std::make_unique<Pansage>();
            case Pokemon::Id::SIMISAGE:
                return std::make_unique<Simisage>();
            case Pokemon::Id::PANSEAR:
                return std::make_unique<Pansear>();
            case Pokemon::Id::SIMISEAR:
                return std::make_unique<Simisear>();
            case Pokemon::Id::PANPOUR:
                return std::make_unique<Panpour>();
            case Pokemon::Id::SIMIPOUR:
                return std::make_unique<Simipour>();
            case Pokemon::Id::MUNNA:
                return std::make_unique<Munna>();
            case Pokemon::Id::MUSHARNA:
                return std::make_unique<Musharna>();
            case Pokemon::Id::PIDOVE:
                return std::make_unique<Pidove>();
            case Pokemon::Id::TRANQUILL:
                return std::make_unique<Tranquill>();
            case Pokemon::Id::UNFEZANT:
                return std::make_unique<Unfezant>();
            case Pokemon::Id::BLITZLE:
                return std::make_unique<Blitzle>();
            case Pokemon::Id::ZEBSTRIKA:
                return std::make_unique<Zebstrika>();
            case Pokemon::Id::ROGGENROLA:
                return std::make_unique<Roggenrola>();
            case Pokemon::Id::BOLDORE:
                return std::make_unique<Boldore>();
            case Pokemon::Id::GIGALITH:
                return std::make_unique<Gigalith>();
            case Pokemon::Id::WOOBAT:
                return std::make_unique<Woobat>();
            case Pokemon::Id::SWOOBAT:
                return std::make_unique<Swoobat>();
            case Pokemon::Id::DRILBUR:
                return std::make_unique<Drilbur>();
            case Pokemon::Id::EXCADRILL:
                return std::make_unique<Excadrill>();
            case Pokemon::Id::AUDINO:
                return std::make_unique<Audino>();
            case Pokemon::Id::TIMBURR:
                return std::make_unique<Timburr>();
            case Pokemon::Id::GURDURR:
                return std::make_unique<Gurdurr>();
            case Pokemon::Id::CONKELDURR:
                return std::make_unique<Conkeldurr>();
            case Pokemon::Id::TYMPOLE:
                return std::make_unique<Tympole>();
            case Pokemon::Id::PALPITOAD:
                return std::make_unique<Palpitoad>();
            case Pokemon::Id::SEISMITOAD:
                return std::make_unique<Seismitoad>();
            case Pokemon::Id::THROH:
                return std::make_unique<Throh>();
            case Pokemon::Id::SAWK:
                return std::make_unique<Sawk>();
            case Pokemon::Id::SEWADDLE:
                break;
            case Pokemon::Id::SWADLOON:
                break;
            case Pokemon::Id::LEAVANNY:
                break;
            case Pokemon::Id::VENIPEDE:
                break;
            case Pokemon::Id::WHIRLIPEDE:
                break;
            case Pokemon::Id::SCOLIPEDE:
                break;
            case Pokemon::Id::COTTONEE:
                break;
            case Pokemon::Id::WHIMSICOTT:
                break;
            case Pokemon::Id::PETILIL:
                break;
            case Pokemon::Id::LILLIGANT:
                break;
            case Pokemon::Id::BASCULIN:
                break;
            case Pokemon::Id::SANDILE:
                break;
            case Pokemon::Id::KROKOROK:
                break;
            case Pokemon::Id::KROOKODILE:
                break;
            case Pokemon::Id::DARUMAKA:
                break;
            case Pokemon::Id::DARMANITAN:
                break;
            case Pokemon::Id::MARACTUS:
                break;
            case Pokemon::Id::DWEBBLE:
                break;
            case Pokemon::Id::CRUSTLE:
                break;
            case Pokemon::Id::SCRAGGY:
                break;
            case Pokemon::Id::SCRAFTY:
                break;
            case Pokemon::Id::SIGILYPH:
                break;
            case Pokemon::Id::YAMASK:
                break;
            case Pokemon::Id::COFAGRIGUS:
                break;
            case Pokemon::Id::TIRTOUGA:
                break;
            case Pokemon::Id::CARRACOSTA:
                break;
            case Pokemon::Id::ARCHEN:
                break;
            case Pokemon::Id::ARCHEOPS:
                break;
            case Pokemon::Id::TRUBBISH:
                break;
            case Pokemon::Id::GARBODOR:
                break;
            case Pokemon::Id::ZORUA:
                break;
            case Pokemon::Id::ZOROARK:
                break;
            case Pokemon::Id::MINCCINO:
                break;
            case Pokemon::Id::CINCCINO:
                break;
            case Pokemon::Id::GOTHITA:
                break;
            case Pokemon::Id::GOTHORITA:
                break;
            case Pokemon::Id::GOTHITELLE:
                break;
            case Pokemon::Id::SOLOSIS:
                break;
            case Pokemon::Id::DUOSION:
                break;
            case Pokemon::Id::REUNICLUS:
                break;
            case Pokemon::Id::DUCKLETT:
                break;
            case Pokemon::Id::SWANNA:
                break;
            case Pokemon::Id::VANILLITE:
                break;
            case Pokemon::Id::VANILLISH:
                break;
            case Pokemon::Id::VANILLUXE:
                break;
            case Pokemon::Id::DEERLING:
                break;
            case Pokemon::Id::SAWSBUCK:
                break;
            case Pokemon::Id::EMOLGA:
                break;
            case Pokemon::Id::KARRABLAST:
                break;
            case Pokemon::Id::ESCAVALIER:
                break;
            case Pokemon::Id::FOONGUS:
                break;
            case Pokemon::Id::AMOONGUSS:
                break;
            case Pokemon::Id::FRILLISH:
                break;
            case Pokemon::Id::JELLICENT:
                break;
            case Pokemon::Id::ALOMONOLA:
                break;
            case Pokemon::Id::JOLTIK:
                break;
            case Pokemon::Id::GALVANTULA:
                break;
            case Pokemon::Id::FERROSEED:
                break;
            case Pokemon::Id::FERROTHORN:
                break;
            case Pokemon::Id::KLINK:
                break;
            case Pokemon::Id::KLANG:
                break;
            case Pokemon::Id::KLINKLANG:
                break;
            case Pokemon::Id::TYNAMO:
                break;
            case Pokemon::Id::EELEKTRIK:
                break;
            case Pokemon::Id::ELEKTROSS:
                break;
            case Pokemon::Id::ELGYEM:
                break;
            case Pokemon::Id::BEHEEYEM:
                break;
            case Pokemon::Id::LITWICK:
                break;
            case Pokemon::Id::LAMPENT:
                break;
            case Pokemon::Id::CHANDELURE:
                break;
            case Pokemon::Id::AXEW:
                break;
            case Pokemon::Id::FRAXURE:
                break;
            case Pokemon::Id::HAXORUS:
                break;
            case Pokemon::Id::CUBCHOO:
                break;
            case Pokemon::Id::BEARTIC:
                break;
            case Pokemon::Id::CRYOGONAL:
                break;
            case Pokemon::Id::SHELMET:
                break;
            case Pokemon::Id::ACCELGOR:
                break;
            case Pokemon::Id::STUNFISH:
                break;
            case Pokemon::Id::MIENFOO:
                break;
            case Pokemon::Id::MINESHAO:
                break;
            case Pokemon::Id::DRUDDIGON:
                break;
            case Pokemon::Id::GOLETT:
                break;
            case Pokemon::Id::GOLURK:
                break;
            case Pokemon::Id::PAWNIARD:
                break;
            case Pokemon::Id::BISHARP:
                break;
            case Pokemon::Id::BOUFFALANT:
                break;
            case Pokemon::Id::RUFFLET:
                break;
            case Pokemon::Id::BRAVIARY:
                break;
            case Pokemon::Id::VULLABY:
                break;
            case Pokemon::Id::MANDIBUZZ:
                break;
            case Pokemon::Id::HEATMOR:
                break;
            case Pokemon::Id::DURANT:
                break;
            case Pokemon::Id::DEINO:
                break;
            case Pokemon::Id::ZWEILOUS:
                break;
            case Pokemon::Id::HYDREIGON:
                return std::make_unique<Hydreigon>();
            case Pokemon::Id::LARVESTA:
                break;
            case Pokemon::Id::VOLCARONA:
                break;
            case Pokemon::Id::COBALION:
                break;
            case Pokemon::Id::TERRAKION:
                break;
            case Pokemon::Id::VIRIZION:
                break;
            case Pokemon::Id::TORNADUS:
                break;
            case Pokemon::Id::THUNDURUS:
                break;
            case Pokemon::Id::RESHIRAM:
                break;
            case Pokemon::Id::ZEKROM:
                break;
            case Pokemon::Id::LANDORUS:
                break;
            case Pokemon::Id::KYUREM:
                break;
            case Pokemon::Id::KELDEO:
                break;
            case Pokemon::Id::MELOETTA:
                break;
            case Pokemon::Id::GENESECT:
                break;
            default:
                return nullptr;
        }
        return nullptr;
    }
}
