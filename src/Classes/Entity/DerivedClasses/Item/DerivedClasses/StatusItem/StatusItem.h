//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct StatusItem : Item {
    StatusItem(const char *id, int quantity);

    [[nodiscard]] std::size_t getClass() const override;

    [[nodiscard]] std::string getEffect() const override = 0;

    [[nodiscard]] virtual StatusCondition getStatus() const = 0;

    void restore(Pokemon &pokemon) const;

    [[nodiscard]] static std::string restoreMessage(const Pokemon &pokemon) ;
};
