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
    BattleItem(int quantity, const char * name, const char * stat);

    std::string getStat() const;
};