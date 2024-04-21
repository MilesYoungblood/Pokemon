//
// Created by miles on 4/20/2024.
//

#pragma once

#include "../Cache.h"

class ItemRegistry final : public Cache<ItemRegistry> {
public:
    ItemRegistry(const ItemRegistry &) = default;

    ItemRegistry(ItemRegistry &&) noexcept = default;

    ItemRegistry &operator=(const ItemRegistry &) = default;

    ItemRegistry &operator=(ItemRegistry &&) noexcept = default;

    ~ItemRegistry() override = default;

    [[nodiscard]] std::string getName(const std::string &id) const;

    [[nodiscard]] std::string getEffect(const std::string &id) const;

    [[nodiscard]] std::string getBattleItemStat(const std::string &id) const;

    [[nodiscard]] std::string getStatusItemStatus(const std::string &id) const;

    [[nodiscard]] int getResourceItemAmount(const std::string &id) const;

    [[nodiscard]] bool getResourceItemTypes(const std::string &id) const;

private:
    set<std::string> names{};
    set<std::string> effects{};

    set<std::string> battleItemStats{};

    set<std::string> statusItemStatuses{};

    set<int> resourceItemAmounts{};
    set<bool> resourceItemTypes{};

    friend class Cache;

    ItemRegistry() = default;
};
