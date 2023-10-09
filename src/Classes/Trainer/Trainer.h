//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include "../Pokemon/Pokemon.h"
#include "../Item/RestoreItem.h"
#include "../Item/StatusItem.h"
#include "../Item/Pokeball.h"
#include "../Item/BattleItem.h"

class Map;

class Trainer : public Entity {
private:
    const char *dialogue;

protected:
    const static int MAX_POKEMON = 6;       // max number of Pokémon per party
    const static int MAX_ITEMS = 50;        // max number of items per bag
    const static int NUM_ITEM_TYPES = 4;    // number of types of items

    int numFainted;                         // number of fainted Pokémon
    int numPokemon;                         // current number of Pokémon in the party
    int numItems[Trainer::NUM_ITEM_TYPES];  // number of each type of item

    Pokemon* party[Trainer::MAX_POKEMON];
    Item* items[Trainer::NUM_ITEM_TYPES][Trainer::MAX_ITEMS];

public:
    Trainer();
    Trainer(int x, int y);
    Trainer(const std::initializer_list<Pokemon*> &pokemon, int x, int y);
    Trainer(const std::initializer_list<Pokemon*> &pokemon, int x, int y, int vision, SDL_Renderer *r);
    Trainer(const Trainer &) = delete;
    Trainer& operator=(const Trainer &) = delete;
    ~Trainer();

    int partySize() const;
    void addPokemon(Pokemon *toAdd);
    void removePokemon(int index);
    void clearParty();

    int getNumItems(int type) const;
    Item& getItem(int type, int item) const;
    void addItem(int type, Item *toAdd);
    void removeItem(int type, int index);

    void setRestoreItems(const std::vector<Item*> &inventory);
    void setStatusItems(const std::vector<Item*> &inventory);
    void setPokeBalls(const std::vector<Item*> &inventory);
    void setBattleItems(const std::vector<Item*> &inventory);

    void incFaintCount();

    __attribute__((unused)) __attribute__((unused)) void decFaintCount();

    void swapPokemon(int first, int second);

    Pokemon& operator[](int spot);
    const Pokemon& operator[](int spot) const;

    virtual explicit operator bool() const;
    virtual bool canFight() const;

    void moveToPlayer(const Map &map, const Trainer *trainer);
};