//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include <filesystem>

#include "../Pokemon/Pokemon.h"
#include "../Item/RestoreItem.h"
#include "../Item/StatusItem.h"
#include "../Item/Pokeball.h"
#include "../Item/BattleItem.h"

inline const std::string PROJECT_PATH = std::filesystem::current_path().parent_path().generic_string();

class Trainer : public Entity {
private:
    const char *dialogue{""};

protected:
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
    auto operator=(const Trainer &) -> Trainer& = delete;
    Trainer(const Trainer &&) = delete;
    auto operator=(const Trainer &&) -> Trainer& = delete;
    virtual ~Trainer();

    [[nodiscard]] auto partySize() const -> int;
    void addPokemon(Pokemon *toAdd);
    void removePokemon(int index);
    void clearParty();

    [[nodiscard]] auto getNumItems(int type) const -> int;
    [[nodiscard]] auto getItem(int type, int item) const -> Item &;

    void addItem(int type, Item *toAdd);
    void removeItem(int type, int index);

    void setRestoreItems(const std::initializer_list<Item*> &inventory);
    void setStatusItems(const std::initializer_list<Item*> &inventory);
    void setPokeBalls(const std::initializer_list<Item*> &inventory);
    void setBattleItems(const std::initializer_list<Item*> &inventory);

    void incFaintCount();

    void decFaintCount();

    void swapPokemon(int first, int second);

    auto operator[](int spot) -> Pokemon&;
    auto operator[](int spot) const -> const Pokemon&;

    virtual explicit operator bool() const;
    [[nodiscard]] virtual auto canFight() const -> bool;
};
