//
// Created by Miles Youngblood on 12/14/2022.
//

#include "Data.h"

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

/// Pokemon

Pokemon Greninja("Greninja", "water", "dark", 50, 300, 95, 67, 103, 71, 122, {WShuriken, DarkPulse, IceBeam, Extrasensory});
Pokemon Charizard("Charizard", "fire", "flying", 50, 300, 84, 78, 109, 85, 100, {Flamethrower, AirSlash, DragonPulse, SolarBeam});
Pokemon Hydreigon("Hydreigon", "dark", "dragon", 50, 300, 105, 90, 125, 90, 98, {DarkPulse, DragonPulse, Flamethrower, FocusBlast});
Pokemon Pikachu("Pikachu", "electric", 50, 300, 55, 40, 50, 50, 90, {Thunder, QuickAttack, IronTail, VoltTackle});
Pokemon Lucario("Lucario", "fighting", "steel", 50, 300, 110, 70, 115, 70, 90, {AuraSphere, FlashCannon, DragonPulse, DarkPulse});

/// Trainers

Trainer Trainer_1({Greninja, Charizard, Hydreigon});
Trainer Trainer_2({Pikachu, Lucario});

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

std::vector<RestoreItem> userRestoreItems = {Potion, Ether};
std::vector<StatusItem> userStatusItems = {ParalyzeHeal, BurnHeal, IceHeal, Antidote, Awakening};
std::vector<PokeBall> userPokeBalls = {pokeBall, GreatBall, UltraBall};
std::vector<BattleItem> userBattleItems = {XAttack, XSpeed};

size_t turn = 1;