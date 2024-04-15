//
// Created by Miles Youngblood on 3/7/2024.
//

#include "StatusCondition.h"

const char *statusToString(const StatusCondition status) {
    switch (status) {
        case StatusCondition::PARALYSIS:
            return "paralysis";

        case StatusCondition::BURN:
            return "burn";

        case StatusCondition::FREEZE:
            return "freezing";

        case StatusCondition::POISON:
            return "poisoning";

        case StatusCondition::SLEEP:
            return "slumber";

        default:
            throw std::runtime_error("Unexpected error: function getStatusAsString");
    }
}
