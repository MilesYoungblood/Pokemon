//
// Created by Miles Youngblood on 7/14/2023.
//

#pragma once

#include <unordered_map>

#include "ItemList/RestoreItems.h"
#include "ItemList/StatusItems.h"
#include "ItemList/PokeBalls.h"
#include "ItemList/BattleItems.h"

struct RestoreItemData {
    const char *name;
    const int amount;
    const bool isHp;
};

inline const std::unordered_map<ItemID, RestoreItemData> RESTORE_ITEMS{
        { ItemID::ETHER,        { "Ether",        5,   false }},
        { ItemID::POTION,       { "Potion",       20,  true }},
        { ItemID::SUPER_POTION, { "Super Potion", 60,  true }},
        { ItemID::HYPER_POTION, { "Hyper Potion", 120, true }}
};

struct StatusItemData {
    const char *name;
    const Status status;
};

inline const std::unordered_map<ItemID, StatusItemData> STATUS_ITEMS{
        { ItemID::ANTIDOTE,      { "Antidote",      Status::POISON }},
        { ItemID::AWAKENING,     { "Awakening",     Status::SLEEP }},
        { ItemID::BURN_HEAL,     { "Burn Heal",     Status::BURN }},
        { ItemID::ICE_HEAL,      { "Ice Heal",      Status::FREEZE }},
        { ItemID::PARALYZE_HEAL, { "Paralyze Heal", Status::PARALYSIS }}
};

struct PokeBallData {
    const char *name;

    double (*catchRate)(const Pokemon &, Time, bool, int);

    void (*postCatch)(Pokemon &);
};

using catchRate = double (*)(const Pokemon &, Time, bool, int);
using postCatch = void (*)(Pokemon &);

inline const std::unordered_map<ItemID, PokeBallData> POKE_BALLS{
        { ItemID::POKE_BALL,    { "Poke Ball",    [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int /*turn*/) -> double {
            return 1.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { ItemID::GREAT_BALL,   { "Great Ball",   [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return 1.5;
        }, [](Pokemon &pokemon) -> void {}}},

        { ItemID::ULTRA_BALL,   { "Ultra Ball",   [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return 2.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { ItemID::MASTER_BALL,  { "Master Ball",  [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int /*turn*/) -> double {
            return 255.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { ItemID::NET_BALL,     { "Net Ball",     [](const Pokemon &pokemon, Time  /*time*/, bool  /*isCave*/, int /*turn*/) -> double {
            if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::BUG or
                pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::BUG) {
                return 3.5;
            }
            return 1.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { ItemID::NEST_BALL,    { "Nest Ball",    [](const Pokemon &pokemon, Time  /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return ((41 - pokemon.getLevel()) * 4069 / 10.0) / 4096.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { ItemID::TIMER_BALL,   { "Timer Ball",   [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int turn) -> double {
            return std::min(1 + turn * 1229 / 4069.0, 4.0);
        }, [](Pokemon &pokemon) -> void {}}},

        { ItemID::PREMIER_BALL, { "Premier Ball", [](const Pokemon & /*pokemon*/, Time /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return 1.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { ItemID::DUSK_BALL,    { "Dusk Ball",    [](const Pokemon & /*pokemon*/, Time time, bool isCave, int  /*turn*/) -> double {
            return time == Time::NIGHT or isCave ? 3.5 : 1.0;
        }, [](Pokemon &pokemon) -> void {}}},

        { ItemID::HEAL_BALL,    { "Heal Ball",    [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int  /*turn*/) -> double {
            return 1.0;
        }, [](Pokemon &pokemon) -> void {
            pokemon.setHP(pokemon.getMaxHp());
        }}},

        { ItemID::QUICK_BALL,   { "Quick Ball",   [](const Pokemon & /*pokemon*/, Time  /*time*/, bool  /*isCave*/, int turn) -> double {
            return turn > 1ULL ? 1.0 : 5.0;
        }, [](Pokemon &pokemon) -> void {}}},
};

struct BattleItemData {
    const char *name;
    const Stat stat;
};

inline const std::unordered_map<ItemID, BattleItemData> BATTLE_ITEMS{
        { ItemID::X_ATTACK,     { "X Attack",      Stat::ATTACK }},
        { ItemID::X_DEFENSE,    { "X Defense",     Stat::DEFENSE }},
        { ItemID::X_SP_ATTACK,  { "X Sp. Attack",  Stat::SP_ATTACK }},
        { ItemID::X_SP_DEFENSE, { "X Sp. Defense", Stat::SP_DEFENSE }},
        { ItemID::X_SPEED,      { "X Speed",       Stat::SPEED }},
        { ItemID::X_ACCURACY,   { "X Accuracy",    Stat::ACCURACY }}
};
