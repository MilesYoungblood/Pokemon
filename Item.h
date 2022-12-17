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
    Item(int quantity, const std::string &name);
    virtual ~Item() = default;

    void setQuantity(int newQuantity);
    int getQuantity() const;

    std::string getName() const;

    friend std::ostream& operator<<(std::ostream &out, const Item &rhs);
};

class RestoreItems : public Item {
private:
    int amount;
    std::string restoreType;

public:
    RestoreItems();
    RestoreItems(int quantity, int amount, const std::string &name, const std::string &restoreType);

    int getAmount() const;
    std::string getRestoreType() const;
};

class StatusItems : public Item {
private:
    std::string restoreType;

public:
    StatusItems();
    StatusItems(const StatusItems &copy);
    StatusItems(int quantity, const std::string &name, const std::string &restoreType);

    std::string getRestoreType() const;
};

class PokeBalls : public Item {
private:
    float catchRate;

public:
    PokeBalls();
    PokeBalls(int quantity, float catchRate, const std::string &name);

    float getCatchRate() const;
};

class BattleItems : public Item {
private:
    std::string stat;

public:
    BattleItems();
    BattleItems(int quantity, const std::string &name, const std::string &stat);

    std::string getStat() const;
};