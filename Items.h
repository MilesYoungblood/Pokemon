//
// Created by miles on 5/25/2022.
//

#ifndef POKEMON_BATTLE_ITEMS_H
#define POKEMON_BATTLE_ITEMS_H

#include "Pokemon.h"
#include <iostream>
#include <unistd.h>

class Items {
private:
    int quantity;
    std::string name;
public:
    Items();
    Items(const Items& copy);
    Items(int quantity, const std::string& name);

    void setQuantity(int newQuantity);
    int getQuantity() const;

    std::string getName() const;

    static void useItem(Items& itemToUse);
    virtual void useItemMessage();
};

class RestoreItems : public Items {
private:
    int amount;
    std::string restoreType;
public:
    RestoreItems();
    RestoreItems(int quantity, int amount, const std::string& name, const std::string& restoreType);

    int getAmount() const;
    std::string getRestoreType() const;
};

class StatusItems : public Items {
private:
    std::string restoreType;
public:
    StatusItems();
    StatusItems(const StatusItems& copy);
    StatusItems(int quantity, const std::string& name, const std::string& restoreType);

    std::string getRestoreType() const;
};

class PokeBalls : public Items {
private:
    double catchRate;
public:
    PokeBalls();
    PokeBalls(int quantity, double catchRate, const std::string& name);

    double getCatchRate() const;

    void useItemMessage() override;
};

class BattleItems : public Items {
private:
    std::string stat;
public:
    BattleItems();
    BattleItems(int quantity, const std::string& name, const std::string& stat);

    std::string getStat() const;
};

#endif //POKEMON_BATTLE_ITEMS_H