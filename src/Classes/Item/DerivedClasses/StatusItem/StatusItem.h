//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"
#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"

class StatusItem : public Item {
public:
    enum class Id {
        ANTIDOTE,
        AWAKENING,
        BURN_HEAL,
        ICE_HEAL,
        PARALYZE_HEAL
    };

    struct Data {
        std::string_view name;
        Status status;
    };

    StatusItem(StatusItem::Id id, int quantity);

    [[nodiscard]] StatusItem::Id getId() const;

    [[nodiscard]] Item::Class getClass() const override;

    void restore(Pokemon &pokemon) const;

    static void restoreMessage(const Pokemon &pokemon);

private:
    StatusItem::Id id;
};
