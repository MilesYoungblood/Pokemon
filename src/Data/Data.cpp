//
// Created by Miles Youngblood on 12/14/2022.
//

#include "Data.h"

/// Moves

WaterShuriken waterShuriken;
Move DarkPulse("Dark Pulse", "dark", "special", 15, 80, 100);
IceBeam iceBeam;
Move Extrasensory("Extrasensory", "psychic", "special", 15, 90, 100);
Flamethrower flamethrower;
Move AirSlash("Air Slash", "flying", "special", 15, 75, 95);
Move DragonPulse("Dragon Pulse", "dragon", "special", 10, 85, 100);
Move SolarBeam("Solar Beam", "grass", "special", 10, 120, 100);
FocusBlast focusBlast;
Thunder thunder;
Move QuickAttack("Quick Attack", "normal", "physical", 30, 40, 100);
IronTail ironTail;
VoltTackle voltTackle;
AuraSphere auraSphere;
FlashCannon flashCannon;

/// Pokemon

Pokemon Greninja("Greninja", "water", "dark", 50, 300, 95, 67, 103, 71, 122);
Pokemon Charizard("Charizard", "fire", "flying", 50, 300, 84, 78, 109, 85, 100);
Pokemon Hydreigon("Hydreigon", "dark", "dragon", 50, 300, 105, 90, 125, 90, 98);
Pokemon Pikachu("Pikachu", "electric", 50, 300, 55, 40, 50, 50, 90);
Pokemon Lucario("Lucario", "fighting", "steel", 50, 300, 110, 70, 115, 70, 90);

/// Trainers

Trainer Trainer_1({ Greninja, Charizard, Hydreigon });
Trainer Trainer_2({ Pikachu, Lucario });

/// Items

const RestoreItem Potion(2, 20, "Potion", "HP");
const RestoreItem Ether(2, 5, "Ether", "PP");

const StatusItem ParalyzeHeal(2, "Paralysis Heal", "paralysis");
const StatusItem BurnHeal(3, "Burn Heal", "burn");
const StatusItem IceHeal(2, "Ice Heal", "freeze");
const StatusItem Antidote(3, "Antidote", "poison");
const StatusItem Awakening(4, "Awakening", "sleep");

const PokeBall pokeBall(5, 1.0f, "Poke Ball");
const PokeBall GreatBall(5, 1.5f, "Great Ball");
const PokeBall UltraBall(5, 2.0f, "Ultra Ball");

const BattleItem XAttack(10, "X-Attack", "attack");
const BattleItem XSpeed(5, "X-Speed", "speed");

std::vector<RestoreItem> userRestoreItems = { Potion, Ether };
std::vector<StatusItem> userStatusItems = { ParalyzeHeal, BurnHeal, IceHeal, Antidote, Awakening };
std::vector<PokeBall> userPokeBalls = { pokeBall, GreatBall, UltraBall };
std::vector<BattleItem> userBattleItems = { XAttack, XSpeed };

size_t turn = 1;