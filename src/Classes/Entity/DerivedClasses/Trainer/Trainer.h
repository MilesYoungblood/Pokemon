//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include "../Pokemon/Pokemon.h"
#include "../../../Item/ItemList.h"

class Trainer : public Entity {
private:
    static const int MAX_POKEMON = 6;                     // max number of Pokémon per party
    static const int MAX_ITEMS = 50;                      // max number of items per bag
    static const int NUM_ITEM_TYPES = 4;                  // number of types of items

    int numFainted = 0;                                   // number of fainted Pokémon

    std::vector<std::unique_ptr<Pokemon>> party;
    std::array<std::vector<std::unique_ptr<Item>>, Trainer::NUM_ITEM_TYPES> items;

    static std::size_t getItemTypeId() {
        static std::size_t lastId = 0ULL;
        return lastId++;
    }

    template<typename I>
    static std::size_t getItemTypeId() {
        static const std::size_t type_id = Trainer::getItemTypeId();
        return type_id;
    }

public:
    Trainer() = default;

    Trainer(const char *name, int x, int y);

    Trainer(const char *name, int x, int y, Direction direction);

    Trainer(const char *name, int x, int y, Direction direction, int vision);

    Trainer(const Trainer &) = delete;

    Trainer(Trainer &&) noexcept = delete;

    Trainer &operator=(const Trainer &) = delete;

    Trainer &operator=(Trainer &&) noexcept = delete;

    ~Trainer() override = default;

    static void init();

    [[nodiscard]] int partySize() const;

    void addPokemon(std::unique_ptr<Pokemon> toAdd);

    void removePokemon(int index);

    void swapPokemon(int a, int b);

    void clearParty();

    template<typename I>
    [[nodiscard]] int getNumItems() const {
        try {
            return static_cast<int>(this->items.at(Trainer::getItemTypeId<I>()).size());
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Unable to retrieve item count: ") + e.what() + '\n');
        }
    }

    template<typename I>
    I &getItem(int index) {
        Item *ptr = this->items.at(Trainer::getItemTypeId<I>())[index].get();
        return *dynamic_cast<I *>(ptr);
    }

    template<typename I>
    const I &getItem(int index) const {
        Item *ptr = this->items.at(Trainer::getItemTypeId<I>())[index].get();
        return *dynamic_cast<I *>(ptr);
    }

    template<typename C, typename I>
    void addItem(std::unique_ptr<I> item) {
        try {
            if (this->items.at(static_cast<std::size_t>(item->getClass())).size() == Trainer::MAX_ITEMS) {
                return;
            }

            for (int i = 0; i < this->items.at(static_cast<std::size_t>(item->getClass())).size(); ++i) {
                // if item already exists within our inventory
                Item *ptr = this->items.at(static_cast<std::size_t>(item->getClass())).at(i).get();
                const C *itm = dynamic_cast<C *>(ptr);

                if (item->getId() == itm->getId()) {
                    this->items.at(Trainer::getItemTypeId<C>())[i]->add(item->getQuantity());
                    return;
                }
            }

            this->items.at(static_cast<std::size_t>(item->getClass())).push_back(std::move(item));
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Error adding item: ") + e.what() + '\n');
        }
    }

    template<typename I>
    void removeItem(int index) {
        try {
            this->items.at(Trainer::getItemTypeId<I>()).erase(this->items.at(Trainer::getItemTypeId<I>()).begin() + index);
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Error removing item: ") + e.what() + '\n');
        }
    }

    void incFaintCount();

    void decFaintCount();

    [[nodiscard]] int getFaintCount() const;

    Pokemon &operator[](int index);

    const Pokemon &operator[](int index) const;

    std::vector<std::unique_ptr<Pokemon>>::iterator begin();

    std::vector<std::unique_ptr<Pokemon>>::iterator end();

    [[nodiscard]] bool canFight() const override;
};
