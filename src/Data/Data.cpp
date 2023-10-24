//
// Created by Miles Youngblood on 12/14/2022.
//

#include "Data.h"

/// Maps

Trainer *Joey = new Trainer({
    new Pikachu({ new Thunder, new QuickAttack, new IronTail, new VoltTackle }),
    new Lucario({ new AuraSphere, new FlashCannon, new DragonPulse, new DarkPulse })
}, 7, 6, 3);

Trainer *Red = new Trainer({
   new Pikachu(),
   new Venasaur(),
   new Charizard()
}, 2, 4, 3);

Map Route_1("Route 1", "TrainerBattle.mp3", 13, 10, { { 6, 0, MapIDs::ROUTE_2, 10, 18 } }, { Joey, Red });

Map Route_2("Route 2", "RivalBattle.mp3", 21, 20, { { 10, 19, MapIDs::ROUTE_1, 6, 1 }, { 0, 10, MapIDs::ROUTE_3, 19, 5 } });

Map Route_3("Route 3", "GymBattle.mp3", 21, 11, { { 20, 5, MapIDs::ROUTE_2, 1, 10 } });

std::array<Map *, 3> maps = { &Route_1, &Route_2, &Route_3 };

int currentMapIndex = 0;
Map *currentMap = maps.at(currentMapIndex);
