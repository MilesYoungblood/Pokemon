//
// Created by Miles Youngblood on 12/14/2022.
//

#include "Data.h"

/// Pokemon

const Pokemon Greninja("Greninja", "water", "dark", 50, 300, 95, 67, 103, 71, 122);
const Pokemon Charizard("Charizard", "fire", "flying", 50, 300, 84, 78, 109, 85, 100);
const Pokemon Hydreigon("Hydreigon", "dark", "dragon", 50, 300, 105, 90, 125, 90, 98);
const Pokemon Pikachu("Pikachu", "electric", 50, 300, 55, 40, 50, 50, 90);
const Pokemon Lucario("Lucario", "fighting", "steel", 50, 300, 110, 70, 115, 70, 90);

/// Trainers

Trainer Trainer_1({ Greninja, Charizard, Hydreigon }, 0, 0);
NPC Trainer_2({ Pikachu, Lucario }, 6, 6, 3);

/// Items

const RestoreItem potion(2, 20, "Potion", "HP");
const RestoreItem ether(2, 5, "Ether", "PP");

const StatusItem paralyzeHeal(2, "Paralysis Heal", "paralysis");
const StatusItem BurnHeal(3, "Burn Heal", "burn");
const StatusItem IceHeal(2, "Ice Heal", "freeze");
const StatusItem Antidote(3, "Antidote", "poison");
const StatusItem Awakening(4, "Awakening", "sleep");

const PokeBall pokeBall(5, 1.0f, "Poke Ball");
const PokeBall GreatBall(5, 1.5f, "Great Ball");
const PokeBall UltraBall(5, 2.0f, "Ultra Ball");

const BattleItem XAttack(10, "X-Attack", "attack");
const BattleItem XSpeed(5, "X-Speed", "speed");

std::vector<RestoreItem> userRestoreItems = { potion, ether };
std::vector<StatusItem> userStatusItems = { paralyzeHeal, BurnHeal, IceHeal, Antidote, Awakening };
std::vector<PokeBall> userPokeBalls = { pokeBall, GreatBall, UltraBall };
std::vector<BattleItem> userBattleItems = { XAttack, XSpeed };