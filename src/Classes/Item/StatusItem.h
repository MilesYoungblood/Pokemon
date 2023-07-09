//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class StatusItem : public Item {
private:
    std::string restoreType;

public:
    StatusItem();
    StatusItem(const StatusItem &copy);
    StatusItem(int quantity, const char * name, const char * restoreType);

    std::string getRestoreType() const;
};