//
// Created by miles on 5/25/2022.
//

#ifndef POKEMON_BATTLE_ITEMS_H
#define POKEMON_BATTLE_ITEMS_H

#include "Pokemon.h"
#include <unistd.h>

class Items {
private:
    int quantity;
    std::string name;
public:
    Items();
    Items(const Items& copy);
    Items(int quantity, const std::string& name);

    void SetQuantity(int quantityToSet);
    int GetQuantity() const;

    void SetName(const std::string& nameToSet);
    std::string GetName() const;

    static void UseItem(Items& itemToUse);
};

class RestoreItems : public Items {
private:
    int amount;
public:
    RestoreItems();
    RestoreItems(int quantity, int restoreAmount, const std::string& nameToSet);

    int GetAmount() const;

    static void ItemErrorMessage(const std::vector<RestoreItems>& items, int item);

    //virtual void Restore();
};

class HPItems : public RestoreItems {
public:
    HPItems();
    HPItems(int quantity, int amount, const std::string& name);
    //static void Restore(Pokemon& pokemon, int restoreAmount);
};

class PPItems : public RestoreItems {
public:
    PPItems();
    PPItems(int quantity, int amount, const std::string& name);
    //static void Restore(Pokemon& pokemon, int restoreAmount, int moveToRestore);
};

class StatusItems : public Items {
public:
    StatusItems();
    StatusItems(const StatusItems& copy);
    StatusItems(int quantity, const std::string& name);

    //virtual void Heal(StatusItems& ItemToUse, Pokemon& pokemonToCure) = 0;

    static void ItemErrorMessage(const std::vector<StatusItems>& items, int item);
};

class ParalysisItems : public StatusItems {
public:
    ParalysisItems();
    ParalysisItems(int quantity, const std::string& name);
    void Heal(StatusItems& ItemToUse, Pokemon& pokemonToCure);
};

class BurnItems : public StatusItems {
public:
    BurnItems();
    BurnItems(int quantity, const std::string& name);
    void Heal(StatusItems& ItemToUse, Pokemon& pokemonToCure);
};

class FreezeItems : public StatusItems {
public:
    FreezeItems();
    FreezeItems(int quantity, const std::string& name);
    void Heal(StatusItems& ItemToUse, Pokemon& pokemonToCure);
};

#endif //POKEMON_BATTLE_ITEMS_H
