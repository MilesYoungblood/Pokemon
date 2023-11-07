//
// Created by Miles Youngblood on 7/14/2023.
//

#pragma once

#include <unordered_map>

#include "DerivedClasses/RestoreItem/DerivedClasses/RestoreItems.h"
#include "DerivedClasses/StatusItem/DerivedClasses/StatusItems.h"
#include "DerivedClasses/Pokeball/DerivedClasses/PokeBalls.h"
#include "DerivedClasses/BattleItem/DerivedClasses/BattleItems.h"

struct RestoreItemData {
    const char *name;
    const int amount;
    const bool isHp;
};

inline const std::unordered_map<Item::ID, RestoreItemData> RESTORE_ITEMS{
        { Item::ID::ETHER,        { "Ether",        5,   false }},
        { Item::ID::POTION,       { "Potion",       20,  true }},
        { Item::ID::SUPER_POTION, { "Super Potion", 60,  true }},
        { Item::ID::HYPER_POTION, { "Hyper Potion", 120, true }}
};

struct StatusItemData {
    const char *name;
    const Status status;
};

inline const std::unordered_map<Item::ID, StatusItemData> STATUS_ITEMS{
        { Item::ID::ANTIDOTE,      { "Antidote",      Status::POISON }},
        { Item::ID::AWAKENING,     { "Awakening",     Status::SLEEP }},
        { Item::ID::BURN_HEAL,     { "Burn Heal",     Status::BURN }},
        { Item::ID::ICE_HEAL,      { "Ice Heal",      Status::FREEZE }},
        { Item::ID::PARALYZE_HEAL, { "Paralyze Heal", Status::PARALYSIS }}
};

struct PokeBallData {
    const char *name;

    double (*catchRate)(const Pokemon &, Time, bool, int);

    void (*postCatch)(Pokemon &);
};

using catchRate = double (*)(const Pokemon &, Time, bool, int);
using postCatch = void (*)(Pokemon &);

inline const std::unordered_map<Item::ID, PokeBallData> POKE_BALLS{
        { Item::ID::POKE_BALL,    { "Poke Ball",    [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int /*turn*/) -> double {
            return 1.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::ID::GREAT_BALL,   { "Great Ball",   [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return 1.5;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::ID::ULTRA_BALL,   { "Ultra Ball",   [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return 2.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::ID::MASTER_BALL,  { "Master Ball",  [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int /*turn*/) -> double {
            return 255.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::ID::NET_BALL,     { "Net Ball",     [](const Pokemon &pokemon, Time  /*time*/, bool  /*isCave*/, int /*turn*/) -> double {
            if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::BUG or
                pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::BUG) {
                return 3.5;
            }
            return 1.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::ID::NEST_BALL,    { "Nest Ball",    [](const Pokemon &pokemon, Time  /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return ((41 - pokemon.getLevel()) * 4069 / 10.0) / 4096.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::ID::TIMER_BALL,   { "Timer Ball",   [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int turn) -> double {
            return std::min(1 + turn * 1229 / 4069.0, 4.0);
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::ID::PREMIER_BALL, { "Premier Ball", [](const Pokemon & /*pokemon*/, Time /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return 1.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::ID::DUSK_BALL,    { "Dusk Ball",    [](const Pokemon & /*pokemon*/, Time time, bool isCave, int  /*turn*/) -> double {
            return time == Time::NIGHT or isCave ? 3.5 : 1.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { Item::ID::HEAL_BALL,    { "Heal Ball",    [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return 1.0;
        }, [](Pokemon &pokemon) -> void {
            pokemon.setHP(pokemon.getMaxHp());
        }}},

        { Item::ID::QUICK_BALL,   { "Quick Ball",   [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int turn) -> double {
            return turn > 1ULL ? 1.0 : 5.0;
        }, [](Pokemon &pokemon) -> void {}}},
};

struct BattleItemData {
    const char *name;
    const Stat stat;
};

inline const std::unordered_map<Item::ID, BattleItemData> BATTLE_ITEMS{
        { Item::ID::X_ATTACK,     { "X Attack",      Stat::ATTACK }},
        { Item::ID::X_DEFENSE,    { "X Defense",     Stat::DEFENSE }},
        { Item::ID::X_SP_ATTACK,  { "X Sp. Attack",  Stat::SP_ATTACK }},
        { Item::ID::X_SP_DEFENSE, { "X Sp. Defense", Stat::SP_DEFENSE }},
        { Item::ID::X_SPEED,      { "X Speed",       Stat::SPEED }},
        { Item::ID::X_ACCURACY,   { "X Accuracy",    Stat::ACCURACY }}
};
