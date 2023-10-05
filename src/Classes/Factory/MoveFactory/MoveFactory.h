//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../../Data/MoveList.h"

struct MoveFactory {
    static Move* getMove(MoveID id);
};
