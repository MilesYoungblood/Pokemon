//
// Created by miles on 5/25/2022.
//

#pragma once

#include <iostream>

class Item {
private:
    int quantity;
    std::string name;

public:
    Item();
    Item(const Item &copy);
    Item(int quantity, const char * name);

    void setQuantity(int newQuantity);
    int getQuantity() const;

    std::string getName() const;

    bool canUse() const;

    friend std::ostream& operator<<(std::ostream &out, const Item &rhs);
};