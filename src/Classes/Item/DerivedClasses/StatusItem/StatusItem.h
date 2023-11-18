//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"
#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"

struct StatusItem : public Item {
    StatusItem() = default;

    explicit StatusItem(int quantity);

    [[nodiscard]] virtual Status getStatus() const = 0;

    [[nodiscard]] Item::Id getId() const override = 0;

    [[nodiscard]] Item::Class getClass() const override;

    [[nodiscard]] std::string getName() const override = 0;

    void restore(Pokemon &pokemon) const;

    static void restoreMessage(const Pokemon &pokemon);
};
