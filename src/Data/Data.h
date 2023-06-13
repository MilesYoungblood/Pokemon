//
// Created by Miles Youngblood on 12/14/2022.
//

#pragma once

#include "../Classes/Trainer/Trainer.h"
#include "MoveList.h"

extern Pokemon Greninja;
extern Pokemon Charizard;
extern Pokemon Hydreigon;
extern Pokemon Pikachu;
extern Pokemon Lucario;

const extern WaterShuriken WShuriken;
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

const extern RestoreItem Potion;
const extern RestoreItem Ether;
const extern StatusItem ParalyzeHeal;
const extern StatusItem BurnHeal;
const extern StatusItem IceHeal;
const extern StatusItem Antidote;
const extern StatusItem Awakening;
const extern PokeBall pokeBall;
const extern PokeBall GreatBall;
const extern PokeBall UltraBall;
const extern BattleItem XAttack;
const extern BattleItem XSpeed;

extern std::vector<RestoreItem> userRestoreItems;
extern std::vector<StatusItem> userStatusItems;
extern std::vector<PokeBall> userPokeBalls;
extern std::vector<BattleItem> userBattleItems;

extern size_t turn;