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
        int amount;
        bool isHp;
    };

    RestoreItem(RestoreItem::Id id, int quantity);

    [[nodiscard]] RestoreItem::Id getId() const;

    [[nodiscard]] Item::Class getClass() const override;

    void restore(Pokemon &pokemon) const;

    virtual void restore(Move &move) const;

    void restoreMessage(const Pokemon &pokemon) const;

    void restoreMessage(const Move &move) const;

private:
    RestoreItem::Id id;
};
