//
// Created by Miles Youngblood on 12/14/2022.
//

#pragma once

#include "Trainer.h"
#include <variant>

extern Pokemon Greninja;
extern Pokemon Charizard;
extern Pokemon Hydreigon;
extern Pokemon Pikachu;
extern Pokemon Lucario;

const extern Move WShuriken;
const extern Move DarkPulse;
const extern Move IceBeam;
const extern Move Extrasensory;
const extern Move Flamethrower;
const extern Move AirSlash;
const extern Move DragonPulse;
const extern Move SolarBeam;
const extern Move FocusBlast;
const extern Move Thunder;
const extern Move QuickAttack;
const extern Move IronTail;
const extern Move VoltTackle;
const extern Move AuraSphere;
const extern Move FlashCannon;

extern Trainer Trainer_1;
extern Trainer Trainer_2;

const extern RestoreItems Potion;
const extern RestoreItems Ether;
const extern StatusItems ParalyzeHeal;
const extern StatusItems BurnHeal;
const extern StatusItems IceHeal;
const extern StatusItems Antidote;
const extern StatusItems Awakening;
const extern PokeBalls PokeBall;
const extern PokeBalls GreatBall;
const extern PokeBalls UltraBall;
const extern BattleItems XAttack;
const extern BattleItems XSpeed;

extern std::vector<RestoreItems> userRestoreItems;
extern std::vector<StatusItems> userStatusItems;
extern std::vector<PokeBalls> userPokeBalls;
extern std::vector<BattleItems> userBattleItems;