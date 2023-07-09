//
// Created by Miles Youngblood on 12/14/2022.
//

#pragma once

#include "../Classes/Trainer/Trainer.h"
#include "../Classes/NPC/NPC.h"
#include "MoveList.h"

extern Pokemon Greninja;
extern Pokemon Charizard;
extern Pokemon Hydreigon;
extern Pokemon Pikachu;
extern Pokemon Lucario;

extern WaterShuriken waterShuriken;
extern Move DarkPulse;
extern IceBeam iceBeam;
extern Move Extrasensory;
extern Flamethrower flamethrower;
extern Move AirSlash;
extern Move DragonPulse;
extern Move SolarBeam;
extern FocusBlast focusBlast;
extern Thunder thunder;
extern Move QuickAttack;
extern IronTail ironTail;
extern VoltTackle voltTackle;
extern AuraSphere auraSphere;
extern FlashCannon flashCannon;

extern Trainer Trainer_1;
extern NPC Trainer_2;

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