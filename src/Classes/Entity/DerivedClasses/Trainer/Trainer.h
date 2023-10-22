//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include <filesystem>

#include "../Pokemon/Pokemon.h"
#include "../../../Item/DerivedClasses/RestoreItem/RestoreItem.h"
#include "../../../Item/DerivedClasses/StatusItem/StatusItem.h"
#include "../../../Item/DerivedClasses/Pokeball/Pokeball.h"
#include "../../../Item/DerivedClasses/BattleItem/BattleItem.h"

inline const std::string PROJECT_PATH = std::filesystem::current_path().parent_path().generic_string();

class Trainer : public Entity {
private:
    const char *dialogue{""};

    const static int MAX_POKEMON = 6;                   // max number of Pokémon per party
    const static int MAX_ITEMS = 50;                    // max number of items per bag
    const static int NUM_ITEM_TYPES = 4;                // number of types of items

    int numFainted{0};                                  // number of fainted Pokémon
    int numPokemon{0};                                  // current number of Pokémon in the party
    std::array<int, Trainer::NUM_ITEM_TYPES> numItems;  // number of each type of item

    std::vector<Pokemon *> party;
    std::array<std::vector<Item *>, Trainer::NUM_ITEM_TYPES> items;

public:
    Trainer();
    Trainer(int x, int y);
    Trainer(const std::initializer_list<Pokemon*> &pokemon, int x, int y);
    Trainer(const std::initializer_list<Pokemon*> &pokemon, int x, int y, int vision);
    Trainer(const Trainer &) = delete;
    Trainer(const Trainer &&) = delete;
    Trainer & operator=(const Trainer &) = delete;
    Trainer & operator=(const Trainer &&) = delete;
    virtual ~Trainer();

    [[nodiscard]] int partySize() const;
    void addPokemon(Pokemon *toAdd);
    void removePokemon(int index);
    void clearParty();

    [[nodiscard]] int getNumItems(int type) const;
    [[nodiscard]] Item & getItem(int type, int item) const;

    void addItem(int type, Item *toAdd);
    void removeItem(int type, int index);

    void setRestoreItems(const std::initializer_list<Item*> &inventory);
    void setStatusItems(const std::initializer_list<Item*> &inventory);
    void setPokeBalls(const std::initializer_list<Item*> &inventory);
    void setBattleItems(const std::initializer_list<Item*> &inventory);

    void incFaintCount();
    void decFaintCount();
    [[nodiscard]] int getFaintCount() const;

    void swapPokemon(int first, int second);

    Pokemon & operator[](int spot);
    const Pokemon & operator[](int spot) const;

    virtual explicit operator bool() const;
    [[nodiscard]] virtual bool canFight() const;
};
