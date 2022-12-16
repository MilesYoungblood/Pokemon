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
    Item(const Item &);
    Item(int, const std::string &);
    virtual ~Item() = default;

    void setQuantity(int);
    int getQuantity() const;

    std::string getName() const;

    friend std::ostream& operator<<(std::ostream &, const Item &);
};

class RestoreItems : public Item {
private:
    int amount;
    std::string restoreType;

public:
    RestoreItems();
    RestoreItems(int, int, const std::string &, const std::string &);

    int getAmount() const;
    std::string getRestoreType() const;
};

class StatusItems : public Item {
private:
    std::string restoreType;

public:
    StatusItems();
    StatusItems(const StatusItems &);
    StatusItems(int, const std::string &, const std::string &);

    std::string getRestoreType() const;
};

class PokeBalls : public Item {
private:
    float catchRate;

public:
    PokeBalls();
    PokeBalls(int, float, const std::string &);

    float getCatchRate() const;
};

class BattleItems : public Item {
private:
    std::string stat;

public:
    BattleItems();
    BattleItems(int, const std::string &, const std::string &);

    std::string getStat() const;
};