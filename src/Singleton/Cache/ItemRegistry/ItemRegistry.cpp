//
// Created by miles on 4/20/2024.
//

#include "ItemRegistry.h"

std::string ItemRegistry::getName(const std::string &id) const {
    return this->names.at(id);
}

std::string ItemRegistry::getEffect(const std::string &id) const {
    return this->effects.at(id);
}

std::string ItemRegistry::getBattleItemStat(const std::string &id) const {
    return this->battleItemStats.at(id);
}

std::string ItemRegistry::getStatusItemStatus(const std::string &id) const {
    return this->statusItemStatuses.at(id);
}

int ItemRegistry::getResourceItemAmount(const std::string &id) const {
    return this->resourceItemAmounts.at(id);
}

bool ItemRegistry::getResourceItemTypes(const std::string &id) const {
    return this->resourceItemTypes.at(id);
}
