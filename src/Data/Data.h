//
// Created by Miles Youngblood on 12/14/2022.
//

#pragma once

#include "../Classes/Map/Map.h"
#include "MoveList.h"
#include "ItemList.h"

// each exit point is assigned an ID that denotes what spot it is in the array,
// and consequently which map it will lead to
enum MapIDs {
    ROUTE_1,
    ROUTE_2,
    ROUTE_3
};

extern Pokemon Greninja;
extern Pokemon Charizard;
extern Pokemon Hydreigon;
extern Pokemon Pikachu;
extern Pokemon Lucario;

extern Trainer Trainer_1;

extern Map Route_1;
extern Map Route_2;
extern Map Route_3;