//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"
#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"

struct StatusItem : public Item {
    explicit StatusItem(int quantity);

    [[nodiscard]] virtual Status getStatus() const = 0;

    [[nodiscard]] Item::ID getID() const override = 0;

    [[nodiscard]] Item::Class getType() const override;

    [[nodiscard]] std::string getName() const override = 0;

    void restore(Pokemon &pokemon) const;

    static void restoreMessage(const Pokemon &pokemon);
};
