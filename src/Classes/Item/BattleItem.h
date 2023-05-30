//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class BattleItem : public Item {
private:
    std::string stat;

public:
    BattleItem();
    BattleItem(int quantity, const std::string &name, const std::string &stat);

    std::string getStat() const;
};