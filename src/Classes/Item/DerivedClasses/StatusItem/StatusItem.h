//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"
#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"

struct StatusItem : public Item {
    enum class Id {
        ANTIDOTE,
        AWAKENING,
        BURN_HEAL,
        ICE_HEAL,
        PARALYZE_HEAL
    };

    explicit StatusItem(int quantity);

    [[nodiscard]] std::string getName() const override = 0;

    [[nodiscard]] std::string getEffect() const override = 0;

    [[nodiscard]] virtual StatusCondition getStatus() const = 0;

    [[nodiscard]] virtual StatusItem::Id getId() const = 0;

    [[nodiscard]] Item::Class getClass() const override;

    void restore(Pokemon &pokemon) const;

    [[nodiscard]] std::string restoreMessage(const Pokemon &pokemon) const;
};

inline std::unordered_map<StatusItem::Id, std::unique_ptr<StatusItem>(*)(int)> statusItems;