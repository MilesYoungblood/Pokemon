//
// Created by Miles Youngblood on 12/14/2022.
//

#include "Data.h"

/// Pokemon

Pokemon Greninja("Greninja", "water", "dark", 50);
Pokemon Charizard("Charizard", "fire", "flying", 50);
Pokemon Hydreigon("Hydreigon", "dark", "dragon", 50);
Pokemon Pikachu("Pikachu", "electric", 50);
Pokemon Lucario("Lucario", "fighting", "steel", 50);

/// Moves

const Move WShuriken("Water Shuriken", "water", "special", 20, 15, 100);
const Move DarkPulse("Dark Pulse", "dark", "special", 15, 80, 100);
const Move IceBeam("Ice Beam", "ice", "special", 10, 90, 100);
const Move Extrasensory("Extrasensory", "psychic", "special", 15, 90, 100);
const Move Flamethrower("Flamethrower", "fire", "special", 15, 90, 100);
const Move AirSlash("Air Slash", "flying", "special", 15, 75, 95);
const Move DragonPulse("Dragon Pulse", "dragon", "special", 10, 85, 100);
const Move SolarBeam("Solar Beam", "grass", "special", 10, 120, 100);
const Move FocusBlast("Focus Blast", "fighting", "special", 5, 120, 70);
const Move Thunder("Thunder", "electric", "special", 10, 110, 70);
const Move QuickAttack("Quick Attack", "normal", "physical", 30, 40, 100);
const Move IronTail("Iron Tail", "steel", "physical", 15, 100, 75);
const Move VoltTackle("Volt Tackle", "electric", "physical", 15, 120, 100);
const Move AuraSphere("Aura Sphere", "fighting", "special", 20, 80, 100);
const Move FlashCannon("Flash Cannon", "steel", "special", 10, 80, 100);

/// Trainers

Trainer Trainer_1({Greninja, Charizard, Hydreigon});
Trainer Trainer_2({Pikachu, Lucario});

/// Items

const RestoreItems Potion(2, 20, "Potion", "HP");
const RestoreItems Ether(2, 5, "Ether", "PP");

const StatusItems ParalyzeHeal(2, "Paralysis Heal", "paralysis");
const StatusItems BurnHeal(3, "Burn Heal", "burn");
const StatusItems IceHeal(2, "Ice Heal", "freeze");
const StatusItems Antidote(3, "Antidote", "poison");
const StatusItems Awakening(4, "Awakening", "sleep");

const PokeBalls PokeBall(5, 1.0f, "Poke Ball");
const PokeBalls GreatBall(5, 1.5f, "Great Ball");
const PokeBalls UltraBall(5, 2.0f, "Ultra Ball");

const BattleItems XAttack(10, "X-Attack", "attack");
const BattleItems XSpeed(5, "X-Speed", "speed");

std::vector<RestoreItems> userRestoreItems = {Potion, Ether};
std::vector<StatusItems> userStatusItems = {ParalyzeHeal, BurnHeal, IceHeal, Antidote, Awakening};
std::vector<PokeBalls> userPokeBalls = {PokeBall, GreatBall, UltraBall};
std::vector<BattleItems> userBattleItems = {XAttack, XSpeed};