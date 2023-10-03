//
// Created by miles on 5/25/2022.
//

#pragma once

#include <iostream>

enum class RestoreType { NONE, HP, PP };
enum class Status { NONE, PARALYSIS, BURN, FREEZE, POISON, SLEEP };
enum class Stat { NONE, ATTACK, SP_ATTACK, DEFENSE, SP_DEFENSE, SPEED, ACCURACY };

class Item {
private:
    int quantity;
    std::string name;

public:
    Item();
    Item(const Item &copy);
    Item(int n, const char * name);

    void setQuantity(int newQuantity);
    int getQuantity() const;

    virtual int getAmount() const;
    virtual RestoreType getRestoreType() const;
    virtual Status getStatus() const;
    virtual Stat getStat() const;

    std::string getName() const;

    explicit operator bool() const;

    friend std::ostream& operator<<(std::ostream &out, const Item &rhs);
};