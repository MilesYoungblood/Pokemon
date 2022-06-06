//
// Created by miles on 5/25/2022.
//

#ifndef POKEMON_BATTLE_ITEMS_H
#define POKEMON_BATTLE_ITEMS_H

#include "Pokemon.h"

class Items {
private:
    int quantity;
    std::string name;
public:
    Items();
    Items(const Items& copy);
    Items(int quantity, const std::string& name);

    void SetQuantity(int newQuantity);
    int GetQuantity() const;

    std::string GetName() const;

    static void UseItem(Items& itemToUse);
};

class RestoreItems : public Items {
private:
    int amount;
    std::string rType;
public:
    RestoreItems();
    RestoreItems(int quantity, int amount, const std::string& name, const std::string& rType);

    int GetAmount() const;
    std::string GetRType() const;
};

class StatusItems : public Items {
private:
    std::string rType;
public:
    StatusItems();
    StatusItems(const StatusItems& copy);
    StatusItems(int quantity, const std::string& name, const std::string& rType);

    std::string GetRType() const;
};

class PokeBalls : public Items {
private:
    double catchRate;
public:
    PokeBalls();
    PokeBalls(int quantity, double catchRate, const std::string& name);

    double GetCatchRate() const;
};

#endif //POKEMON_BATTLE_ITEMS_H