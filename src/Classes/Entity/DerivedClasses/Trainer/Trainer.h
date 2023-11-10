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
    const static int MAX_POKEMON = 6;                     // max number of Pokémon per party
    const static int MAX_ITEMS = 50;                      // max number of items per bag
    const static int NUM_ITEM_TYPES = 4;                  // number of types of items

    int numFainted = 0;                                   // number of fainted Pokémon
    int numPokemon = 0;                                   // current number of Pokémon in the party
    std::array<int, Trainer::NUM_ITEM_TYPES> numItems{};  // number of each type of item

    std::vector<std::unique_ptr<Pokemon>> party;
    std::array<std::vector<std::unique_ptr<Item>>, Trainer::NUM_ITEM_TYPES> items;

    static std::size_t getItemTypeId() {
        static std::size_t lastId = 0ULL;
        return lastId++;
    }

    template<typename I>
    static std::size_t getItemTypeId() {
        const static std::size_t type_id = getItemTypeId();
        return type_id;
    }

public:
    Trainer() = default;

    Trainer(const char *name, int x, int y);

    Trainer(const char *name, int x, int y, int direction);

    Trainer(const char *name, int x, int y, int direction, int vision);

    Trainer(const Trainer &) = delete;

    Trainer(Trainer &&) = delete;

    Trainer &operator=(const Trainer &) = delete;

    Trainer &operator=(Trainer &&) = delete;

    ~Trainer() override = default;

    static void init();

    [[nodiscard]] int partySize() const;

    void addPokemon(std::unique_ptr<Pokemon> toAdd);

    template<typename P>
    void addPokemon() {
        try {
            if (this->numPokemon == Trainer::MAX_POKEMON) {
                return;
            }

            this->party.push_back(std::make_unique<P>());
            ++this->numPokemon;
        }
        catch (const std::exception &exception) {
            throw std::runtime_error(std::string("Error adding Pokemon: ") + exception.what() + '\n');
        }
    }

    void removePokemon(int index);

    void swapPokemon(int first, int second);

    void clearParty();

    template<typename I>
    [[nodiscard]] int getNumItems() const {
        try {
            return this->numItems.at(getItemTypeId<I>());
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Unable to retrieve item count: ") + e.what() + '\n');
        }
    }

    template<typename I>
    I &getItem(int index) {
        try {
            Item *ptr = this->items.at(getItemTypeId<I>())[index].get();
            return *static_cast<I *>(ptr);
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Unable to retrieve item: ") + e.what() + '\n');
        }
    }

    template<typename I>
    const I &getItem(int index) const {
        try {
            Item *ptr = this->items.at(getItemTypeId<I>())[index].getKey();
            return *static_cast<I *>(ptr);
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Unable to retrieve item: ") + e.what() + '\n');
        }
    }

    void addItem(std::unique_ptr<Item> toAdd);

    template<typename I>
    void addItem(int quantity) {
        try {
            std::unique_ptr<I> item = std::make_unique<I>(quantity);
            const int type = static_cast<int>(item->getType());
            if (this->numItems.at(type) == Trainer::MAX_ITEMS) {
                return;
            }

            for (int i = 0; i < this->numItems.at(type); ++i) {
                // if item already exists within our inventory
                if (item->getID() == this->items.at(type)[i]->getID()) {
                    this->items.at(type)[i]->add(quantity);
                    return;
                }
            }

            this->items.at(type).push_back(std::move(item));
            ++this->numItems.at(type);
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Error adding item: ") + e.what() + '\n');
        }
    }

    void removeItem(int type, int index);

    void incFaintCount();

    void decFaintCount();

    [[nodiscard]] int getFaintCount() const;

    Pokemon &operator[](int spot);

    const Pokemon &operator[](int spot) const;

    explicit operator bool() const override;

    [[nodiscard]] virtual bool canFight() const;
};
