//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../Classes/Entity/DerivedClasses/Pokemon/Pokedex.h"

namespace PokemonFactory {
    template<typename ...Args>
    inline std::unique_ptr<Pokemon> getPokemon(Pokemon::Id id, Args ...args) {
        switch (id) {
            case Pokemon::Id::VICTINI:
                return std::make_unique<Victini>(args...);
            case Pokemon::Id::SNIVY:
                return std::make_unique<Snivy>(args...);
            case Pokemon::Id::SERVINE:
                return std::make_unique<Servine>(args...);
            case Pokemon::Id::SERPERIOR:
                return std::make_unique<Serperior>(args...);
            case Pokemon::Id::TEPIG:
                return std::make_unique<Tepig>(args...);
            case Pokemon::Id::PIGNITE:
                return std::make_unique<Pignite>(args...);
            case Pokemon::Id::EMBOAR:
                return std::make_unique<Emboar>(args...);
            case Pokemon::Id::OSHAWOTT:
                return std::make_unique<Oshawott>(args...);
            case Pokemon::Id::DEWOTT:
                return std::make_unique<Dewott>(args...);
            case Pokemon::Id::SAMUROTT:
                return std::make_unique<Samurott>(args...);
            case Pokemon::Id::PATRAT:
                return std::make_unique<Patrat>(args...);
            case Pokemon::Id::WATCHOG:
                return std::make_unique<Watchog>(args...);
            case Pokemon::Id::LILLIPUP:
                return std::make_unique<Lillipup>(args...);
            case Pokemon::Id::HERDIER:
                return std::make_unique<Herdier>(args...);
            case Pokemon::Id::STOUTLAND:
                return std::make_unique<Stoutland>(args...);
            case Pokemon::Id::PURRLOIN:
                return std::make_unique<Purrloin>(args...);
            case Pokemon::Id::LIEPARD:
                return std::make_unique<Liepard>(args...);
            case Pokemon::Id::PANSAGE:
                return std::make_unique<Pansage>(args...);
            case Pokemon::Id::SIMISAGE:
                return std::make_unique<Simisage>(args...);
            case Pokemon::Id::PANSEAR:
                return std::make_unique<Pansear>(args...);
            case Pokemon::Id::SIMISEAR:
                return std::make_unique<Simisear>(args...);
            case Pokemon::Id::PANPOUR:
                return std::make_unique<Panpour>(args...);
            case Pokemon::Id::SIMIPOUR:
                return std::make_unique<Simipour>(args...);
            case Pokemon::Id::MUNNA:
                return std::make_unique<Munna>(args...);
            case Pokemon::Id::MUSHARNA:
                return std::make_unique<Musharna>(args...);
            case Pokemon::Id::PIDOVE:
                return std::make_unique<Pidove>(args...);
            case Pokemon::Id::TRANQUILL:
                return std::make_unique<Tranquill>(args...);
            case Pokemon::Id::UNFEZANT:
                return std::make_unique<Unfezant>(args...);
            case Pokemon::Id::BLITZLE:
                return std::make_unique<Blitzle>(args...);
            case Pokemon::Id::ZEBSTRIKA:
                return std::make_unique<Zebstrika>(args...);
            case Pokemon::Id::ROGGENROLA:
                return std::make_unique<Roggenrola>(args...);
            case Pokemon::Id::BOLDORE:
                return std::make_unique<Boldore>(args...);
            case Pokemon::Id::GIGALITH:
                return std::make_unique<Gigalith>(args...);
            case Pokemon::Id::WOOBAT:
                return std::make_unique<Woobat>(args...);
            case Pokemon::Id::SWOOBAT:
                return std::make_unique<Swoobat>(args...);
            case Pokemon::Id::DRILBUR:
                return std::make_unique<Drilbur>(args...);
            case Pokemon::Id::EXCADRILL:
                return std::make_unique<Excadrill>(args...);
            case Pokemon::Id::AUDINO:
                return std::make_unique<Audino>(args...);
            case Pokemon::Id::TIMBURR:
                return std::make_unique<Timburr>(args...);
            case Pokemon::Id::GURDURR:
                return std::make_unique<Gurdurr>(args...);
            case Pokemon::Id::CONKELDURR:
                return std::make_unique<Conkeldurr>(args...);
            case Pokemon::Id::TYMPOLE:
                return std::make_unique<Tympole>(args...);
            case Pokemon::Id::PALPITOAD:
                return std::make_unique<Palpitoad>(args...);
            case Pokemon::Id::SEISMITOAD:
                return std::make_unique<Seismitoad>(args...);
            case Pokemon::Id::THROH:
                return std::make_unique<Throh>(args...);
            case Pokemon::Id::SAWK:
                return std::make_unique<Sawk>(args...);
            case Pokemon::Id::SEWADDLE:
                return std::make_unique<Sewaddle>(args...);
            case Pokemon::Id::SWADLOON:
                return std::make_unique<Swadloon>(args...);
            case Pokemon::Id::LEAVANNY:
                return std::make_unique<Leavanny>(args...);
            case Pokemon::Id::VENIPEDE:
                return std::make_unique<Venipede>(args...);
            case Pokemon::Id::WHIRLIPEDE:
                return std::make_unique<Whirlipede>(args...);
            case Pokemon::Id::SCOLIPEDE:
                return std::make_unique<Scolipede>(args...);
            case Pokemon::Id::COTTONEE:
                return std::make_unique<Cottonee>(args...);
            case Pokemon::Id::WHIMSICOTT:
                return std::make_unique<Whimsicott>(args...);
            case Pokemon::Id::PETILIL:
                return std::make_unique<Petilil>(args...);
            case Pokemon::Id::LILLIGANT:
                return std::make_unique<Lilligant>(args...);
            case Pokemon::Id::BASCULIN:
                return std::make_unique<Basculin>(args...);
            case Pokemon::Id::SANDILE:
                return std::make_unique<Sandile>(args...);
            case Pokemon::Id::KROKOROK:
                return std::make_unique<Krokorok>(args...);
            case Pokemon::Id::KROOKODILE:
                return std::make_unique<Krookodile>(args...);
            case Pokemon::Id::DARUMAKA:
                return std::make_unique<Darumaka>(args...);
            case Pokemon::Id::DARMANITAN:
                return std::make_unique<Darmanitan>(args...);
            case Pokemon::Id::MARACTUS:
                return std::make_unique<Maractus>(args...);
            case Pokemon::Id::DWEBBLE:
                return std::make_unique<Dwebble>(args...);
            case Pokemon::Id::CRUSTLE:
                return std::make_unique<Crustle>(args...);
            case Pokemon::Id::SCRAGGY:
                return std::make_unique<Scraggy>(args...);
            case Pokemon::Id::SCRAFTY:
                return std::make_unique<Scrafty>(args...);
            case Pokemon::Id::SIGILYPH:
                return std::make_unique<Sigilyph>(args...);
            case Pokemon::Id::YAMASK:
                return std::make_unique<Yamask>(args...);
            case Pokemon::Id::COFAGRIGUS:
                return std::make_unique<Cofagrigus>(args...);
            case Pokemon::Id::TIRTOUGA:
                return std::make_unique<Tirtouga>(args...);
            case Pokemon::Id::CARRACOSTA:
                return std::make_unique<Carracosta>(args...);
            case Pokemon::Id::ARCHEN:
                return std::make_unique<Archen>(args...);
            case Pokemon::Id::ARCHEOPS:
                return std::make_unique<Archeops>(args...);
            case Pokemon::Id::TRUBBISH:
                return std::make_unique<Trubbish>(args...);
            case Pokemon::Id::GARBODOR:
                return std::make_unique<Garbodor>(args...);
            case Pokemon::Id::ZORUA:
                return std::make_unique<Zorua>(args...);
            case Pokemon::Id::ZOROARK:
                return std::make_unique<Zoroark>(args...);
            case Pokemon::Id::MINCCINO:
                return std::make_unique<Minccino>(args...);
            case Pokemon::Id::CINCCINO:
                return std::make_unique<Cinccino>(args...);
            case Pokemon::Id::GOTHITA:
                return std::make_unique<Gothita>(args...);
            case Pokemon::Id::GOTHORITA:
                return std::make_unique<Gothorita>(args...);
            case Pokemon::Id::GOTHITELLE:
                return std::make_unique<Gothitelle>(args...);
            case Pokemon::Id::SOLOSIS:
                return std::make_unique<Solosis>(args...);
            case Pokemon::Id::DUOSION:
                return std::make_unique<Duosion>(args...);
            case Pokemon::Id::REUNICLUS:
                return std::make_unique<Reuniclus>(args...);
            case Pokemon::Id::DUCKLETT:
                return std::make_unique<Ducklett>(args...);
            case Pokemon::Id::SWANNA:
                return std::make_unique<Swanna>(args...);
            case Pokemon::Id::VANILLITE:
                return std::make_unique<Vanillite>(args...);
            case Pokemon::Id::VANILLISH:
                return std::make_unique<Vanillish>(args...);
            case Pokemon::Id::VANILLUXE:
                return std::make_unique<Vanilluxe>(args...);
            case Pokemon::Id::DEERLING:
                return std::make_unique<Deerling>(args...);
            case Pokemon::Id::SAWSBUCK:
                return std::make_unique<Sawsbuck>(args...);
            case Pokemon::Id::EMOLGA:
                return std::make_unique<Emolga>(args...);
            case Pokemon::Id::KARRABLAST:
                return std::make_unique<Karrablast>(args...);
            case Pokemon::Id::ESCAVALIER:
                return std::make_unique<Escavalier>(args...);
            case Pokemon::Id::FOONGUS:
                return std::make_unique<Foongus>(args...);
            case Pokemon::Id::AMOONGUSS:
                return std::make_unique<Amoonguss>(args...);
            case Pokemon::Id::FRILLISH:
                return std::make_unique<Frillish>(args...);
            case Pokemon::Id::JELLICENT:
                return std::make_unique<Jellicent>(args...);
            case Pokemon::Id::ALOMOMOLA:
                return std::make_unique<Alomomola>(args...);
            case Pokemon::Id::JOLTIK:
                return std::make_unique<Joltik>(args...);
            case Pokemon::Id::GALVANTULA:
                return std::make_unique<Galvantula>(args...);
            case Pokemon::Id::FERROSEED:
                return std::make_unique<Ferroseed>(args...);
            case Pokemon::Id::FERROTHORN:
                return std::make_unique<Ferrothorn>(args...);
            case Pokemon::Id::KLINK:
                return std::make_unique<Klink>(args...);
            case Pokemon::Id::KLANG:
                return std::make_unique<Klang>(args...);
            case Pokemon::Id::KLINKLANG:
                return std::make_unique<Klinklang>(args...);
            case Pokemon::Id::TYNAMO:
                return std::make_unique<Tynamo>(args...);
            case Pokemon::Id::EELEKTRIK:
                return std::make_unique<Eelektrik>(args...);
            case Pokemon::Id::EELEKTROSS:
                return std::make_unique<Eelektross>(args...);
            case Pokemon::Id::ELGYEM:
                return std::make_unique<Elgyem>(args...);
            case Pokemon::Id::BEHEEYEM:
                return std::make_unique<Beheeyem>(args...);
            case Pokemon::Id::LITWICK:
                return std::make_unique<Litwick>(args...);
            case Pokemon::Id::LAMPENT:
                return std::make_unique<Lampent>(args...);
            case Pokemon::Id::CHANDELURE:
                return std::make_unique<Chandelure>(args...);
            case Pokemon::Id::AXEW:
                return std::make_unique<Axew>(args...);
            case Pokemon::Id::FRAXURE:
                return std::make_unique<Fraxure>(args...);
            case Pokemon::Id::HAXORUS:
                return std::make_unique<Haxorus>(args...);
            case Pokemon::Id::CUBCHOO:
                return std::make_unique<Cubchoo>(args...);
            case Pokemon::Id::BEARTIC:
                return std::make_unique<Beartic>(args...);
            case Pokemon::Id::CRYOGONAL:
                return std::make_unique<Cryogonal>(args...);
            case Pokemon::Id::SHELMET:
                return std::make_unique<Shelmet>(args...);
            case Pokemon::Id::ACCELGOR:
                return std::make_unique<Accelgor>(args...);
            case Pokemon::Id::STUNFISK:
                return std::make_unique<Stunfisk>(args...);
            case Pokemon::Id::MIENFOO:
                return std::make_unique<Mienfoo>(args...);
            case Pokemon::Id::MIENSHAO:
                return std::make_unique<Mienshao>(args...);
            case Pokemon::Id::DRUDDIGON:
                return std::make_unique<Druddigon>(args...);
            case Pokemon::Id::GOLETT:
                return std::make_unique<Golett>(args...);
            case Pokemon::Id::GOLURK:
                return std::make_unique<Golurk>(args...);
            case Pokemon::Id::PAWNIARD:
                return std::make_unique<Pawniard>(args...);
            case Pokemon::Id::BISHARP:
                return std::make_unique<Bisharp>(args...);
            case Pokemon::Id::BOUFFALANT:
                return std::make_unique<Bouffalant>(args...);
            case Pokemon::Id::RUFFLET:
                return std::make_unique<Rufflet>(args...);
            case Pokemon::Id::BRAVIARY:
                return std::make_unique<Braviary>(args...);
            case Pokemon::Id::VULLABY:
                return std::make_unique<Vullaby>(args...);
            case Pokemon::Id::MANDIBUZZ:
                return std::make_unique<Mandibuzz>(args...);
            case Pokemon::Id::HEATMOR:
                return std::make_unique<Heatmor>(args...);
            case Pokemon::Id::DURANT:
                return std::make_unique<Durant>(args...);
            case Pokemon::Id::DEINO:
                return std::make_unique<Deino>(args...);
            case Pokemon::Id::ZWEILOUS:
                return std::make_unique<Zweilous>(args...);
            case Pokemon::Id::HYDREIGON:
                return std::make_unique<Hydreigon>(args...);
            case Pokemon::Id::LARVESTA:
                return std::make_unique<Larvesta>(args...);
            case Pokemon::Id::VOLCARONA:
                return std::make_unique<Volcarona>(args...);
            case Pokemon::Id::COBALION:
                return std::make_unique<Cobalion>(args...);
            case Pokemon::Id::TERRAKION:
                return std::make_unique<Terrakion>(args...);
            case Pokemon::Id::VIRIZION:
                return std::make_unique<Virizion>(args...);
            case Pokemon::Id::TORNADUS:
                return std::make_unique<Tornadus>(args...);
            case Pokemon::Id::THUNDURUS:
                return std::make_unique<Thundurus>(args...);
            case Pokemon::Id::RESHIRAM:
                return std::make_unique<Reshiram>(args...);
            case Pokemon::Id::ZEKROM:
                return std::make_unique<Zekrom>(args...);
            case Pokemon::Id::LANDORUS:
                return std::make_unique<Landorus>(args...);
            case Pokemon::Id::KYUREM:
                return std::make_unique<Kyurem>(args...);
            case Pokemon::Id::KELDEO:
                return std::make_unique<Keldeo>(args...);
            case Pokemon::Id::MELOETTA:
                return std::make_unique<Meloetta>(args...);
            case Pokemon::Id::GENESECT:
                return std::make_unique<Genesect>(args...);
            default:
                return nullptr;
        }
    }
}
