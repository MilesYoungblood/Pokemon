//
// Created by Miles Youngblood on 12/14/2022.
//

#pragma once

#include "../Classes/Trainer/Trainer.h"
#include "../Classes/NPC/NPC.h"
#include "MoveList.h"
#include "ItemList.h"

extern const Pokemon Greninja;
extern const Pokemon Charizard;
extern const Pokemon Hydreigon;
extern const Pokemon Pikachu;
extern const Pokemon Lucario;

extern Trainer Trainer_1;
extern NPC Trainer_2;

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