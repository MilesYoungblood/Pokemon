//
// Created by Miles Youngblood on 3/7/2024.
//

#pragma once

enum class StatusCondition : Uint8 {
    NONE, BURN, PARALYSIS, FREEZE, POISON, SLEEP
};

const char *statusToString(StatusCondition status);
