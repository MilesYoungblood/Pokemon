//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class BattleItem : public Item {
private:
    Stat stat;

public:
    BattleItem();
    BattleItem(int quantity, const char * name, Stat stat);

    Stat getStat() const override;
};