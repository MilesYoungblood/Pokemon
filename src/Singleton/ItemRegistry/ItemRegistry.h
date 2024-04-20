//
// Created by miles on 4/20/2024.
//

#pragma once

#include "../Singleton.h"

class ItemRegistry final : public Singleton<ItemRegistry> {
public:
    [[nodiscard]] std::string getName(const std::string &id) const;

    [[nodiscard]] std::string getEffect(const std::string &id) const;

    [[nodiscard]] std::string getBattleItemStat(const std::string &id) const;

    [[nodiscard]] std::string getStatusItemStatus(const std::string &id) const;

    [[nodiscard]] int getResourceItemAmount(const std::string &id) const;

    [[nodiscard]] bool getResourceItemTypes(const std::string &id) const;

private:
    template<typename T>
    using set = std::unordered_map<std::string, T>;

    set<std::string> names;
    set<std::string> effects;

    set<std::string> battleItemStats;

    set<std::string> statusItemStatuses;

    set<int> resourceItemAmounts;
    set<bool> resourceItemTypes;

    friend class Singleton;

    ItemRegistry() = default;
};
