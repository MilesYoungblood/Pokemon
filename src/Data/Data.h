//
// Created by Miles Youngblood on 12/14/2022.
//

#pragma once

#include "../Classes/Trainer/Trainer.h"
#include "../Classes/NPC/NPC.h"
#include "../Classes/Map/Map.h"
#include "MoveList.h"
#include "ItemList.h"

enum MapIDs { ROUTE_1 = 0, ROUTE_2 = 1, ROUTE_3 = 2 };

extern Pokemon Greninja;
extern Pokemon Charizard;
extern Pokemon Hydreigon;
extern Pokemon Pikachu;
extern Pokemon Lucario;

extern Trainer Trainer_1;

const extern RestoreItem potion;
const extern RestoreItem ether;
const extern StatusItem paralyzeHeal;
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

extern Map Route_1;
extern Map Route_2;
extern Map Route_3;