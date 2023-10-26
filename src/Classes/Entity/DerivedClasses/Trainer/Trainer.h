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
    const static int MAX_POKEMON = 6;                   // max number of Pokémon per party
    const static int MAX_ITEMS = 50;                    // max number of items per bag
    const static int NUM_ITEM_TYPES = 4;                // number of types of items

    int numFainted{0};                                  // number of fainted Pokémon
    int numPokemon{0};                                  // current number of Pokémon in the party
    std::array<int, Trainer::NUM_ITEM_TYPES> numItems;  // number of each type of item

    std::vector<std::unique_ptr<Pokemon>> party;
    std::array<std::vector<std::unique_ptr<Item>>, Trainer::NUM_ITEM_TYPES> items;

public:
    Trainer();
    Trainer(int x, int y);
    Trainer(int x, int y, int direction);
    Trainer(int x, int y, int direction, int vision);
    Trainer(const Trainer &) = delete;
    Trainer(const Trainer &&) = delete;
    Trainer & operator=(const Trainer &) = delete;
    Trainer & operator=(const Trainer &&) = delete;
    virtual ~Trainer();

    [[nodiscard]] int partySize() const;
    inline void addPokemon(std::unique_ptr<Pokemon> toAdd) {
        if (this->numPokemon == Trainer::MAX_POKEMON) {
            return;
        }

        this->party.push_back(std::move(toAdd));
        ++this->numPokemon;
    }
    template <typename P>
    inline void addPokemon() {
        try {
            if (this->numPokemon == Trainer::MAX_POKEMON) {
                return;
            }

            this->party.push_back(std::make_unique<P>());
            ++this->numPokemon;
        }
        catch (const std::exception &exception) {
            throw std::runtime_error(std::string("Error adding Pokemon: ") + exception.what());
        }
    }
    void removePokemon(int index);
    void swapPokemon(int first, int second);
    void clearParty();

    [[nodiscard]] int getNumItems(int type) const;
    [[nodiscard]] Item & getItem(int type, int item) const;

    void addItem(std::unique_ptr<Item> toAdd);
    void removeItem(int type, int index);

    void incFaintCount();
    void decFaintCount();
    [[nodiscard]] int getFaintCount() const;

    Pokemon & operator[](int spot);
    const Pokemon & operator[](int spot) const;

    virtual explicit operator bool() const;
    [[nodiscard]] virtual bool canFight() const;
};
