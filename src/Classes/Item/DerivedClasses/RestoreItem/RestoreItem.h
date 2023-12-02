//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

class RestoreItem : public Item {
public:
    enum class Id {
        POTION,
        SUPER_POTION,
        HYPER_POTION,
        MAX_POTION,
        ETHER,
        MAX_ETHER,
    };

    struct Data {
        std::string_view name;
        const int amount;
        const bool isHp;
    };

    RestoreItem(RestoreItem::Id id, int quantity);

    static void init(RestoreItem::Data (*instructions)(RestoreItem::Id));

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] int getAmount() const;

    [[nodiscard]] bool isHp() const;

    [[nodiscard]] RestoreItem::Id getId() const;

    [[nodiscard]] Item::Class getClass() const override;

    void restore(Pokemon &pokemon) const;

    virtual void restore(Move &move) const;

    void restoreMessage(const Pokemon &pokemon) const;

    void restoreMessage(const Move &move) const;

private:
    RestoreItem::Id id;

    inline static RestoreItem::Data (*dataFunction)(RestoreItem::Id){ nullptr };
};
