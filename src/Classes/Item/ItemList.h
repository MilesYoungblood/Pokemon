//
// Created by Miles Youngblood on 7/14/2023.
//

#pragma once

#include "DerivedClasses/RestoreItem/DerivedClasses/RestoreItems.h"
#include "DerivedClasses/StatusItem/DerivedClasses/StatusItems.h"
#include "DerivedClasses/Pokeball/DerivedClasses/PokeBalls.h"
#include "DerivedClasses/BattleItem/DerivedClasses/BattleItems.h"

struct RestoreItemData {
    const char *name;
    const int amount;
    const bool isHp;
};

inline const std::unordered_map<Item::Id, RestoreItemData> RESTORE_ITEMS{
        { Item::Id::ETHER,        { "Ether",        5,   false }},
        { Item::Id::POTION,       { "Potion",       20,  true }},
        { Item::Id::SUPER_POTION, { "Super Potion", 60,  true }},
        { Item::Id::HYPER_POTION, { "Hyper Potion", 120, true }}
};

struct StatusItemData {
    const char *name;
    const Status status;
};

inline const std::unordered_map<Item::Id, StatusItemData> STATUS_ITEMS{
        { Item::Id::ANTIDOTE,      { "Antidote",      Status::POISON }},
        { Item::Id::AWAKENING,     { "Awakening",     Status::SLEEP }},
        { Item::Id::BURN_HEAL,     { "Burn Heal",     Status::BURN }},
        { Item::Id::ICE_HEAL,      { "Ice Heal",      Status::FREEZE }},
        { Item::Id::PARALYZE_HEAL, { "Paralyze Heal", Status::PARALYSIS }}
};

struct PokeBallData {
    const char *name;

    double (*catchRate)(const Pokemon &, Time, bool, int);

    void (*postCatch)(Pokemon &);
};

inline const std::unordered_map<Item::Id, PokeBallData> POKE_BALLS{
        { Item::Id::POKE_BALL,    { "Poke Ball",    [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int /*turn*/) -> double {
            return 1.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::Id::GREAT_BALL,   { "Great Ball",   [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return 1.5;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::Id::ULTRA_BALL,   { "Ultra Ball",   [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return 2.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::Id::MASTER_BALL,  { "Master Ball",  [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int /*turn*/) -> double {
            return 255.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::Id::NET_BALL,     { "Net Ball",     [](const Pokemon &pokemon, Time  /*time*/, bool  /*isCave*/, int /*turn*/) -> double {
            if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::BUG or
                pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::BUG) {
                return 3.5;
            }
            return 1.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::Id::NEST_BALL,    { "Nest Ball",    [](const Pokemon &pokemon, Time  /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return ((41 - pokemon.getLevel()) * 4069 / 10.0) / 4096.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::Id::TIMER_BALL,   { "Timer Ball",   [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int turn) -> double {
            return std::min(1 + turn * 1229 / 4069.0, 4.0);
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::Id::PREMIER_BALL, { "Premier Ball", [](const Pokemon & /*pokemon*/, Time /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return 1.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::Id::DUSK_BALL,    { "Dusk Ball",    [](const Pokemon & /*pokemon*/, Time time, bool isCave, int  /*turn*/) -> double {
            return time == Time::NIGHT or isCave ? 3.5 : 1.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::Id::HEAL_BALL,    { "Heal Ball",    [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return 1.0;
        }, [](Pokemon &pokemon) -> void {
            pokemon.setHP(pokemon.getMaxHp());
        }}},

        { Item::Id::QUICK_BALL,   { "Quick Ball",   [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int turn) -> double {
            return turn > 1ULL ? 1.0 : 5.0;
        }, [](Pokemon &pokemon) -> void {}}},
};

struct BattleItemData {
    const char *name;
    const Stat stat;
};

inline const std::unordered_map<Item::Id, BattleItemData> BATTLE_ITEMS{
        { Item::Id::X_ATTACK,     { "X Attack",      Stat::ATTACK }},
        { Item::Id::X_DEFENSE,    { "X Defense",     Stat::DEFENSE }},
        { Item::Id::X_SP_ATTACK,  { "X Sp. Attack",  Stat::SP_ATTACK }},
        { Item::Id::X_SP_DEFENSE, { "X Sp. Defense", Stat::SP_DEFENSE }},
        { Item::Id::X_SPEED,      { "X Speed",       Stat::SPEED }},
        { Item::Id::X_ACCURACY,   { "X Accuracy",    Stat::ACCURACY }}
};
