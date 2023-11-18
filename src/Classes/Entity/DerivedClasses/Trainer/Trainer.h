//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include "../Pokemon/Pokemon.h"
#include "../../../Item/ItemList.h"

class Trainer : public Entity {
private:
    const static int MAX_POKEMON = 6;                     // max number of Pokémon per party
    const static int MAX_ITEMS = 50;                      // max number of items per bag
    const static int NUM_ITEM_TYPES = 4;                  // number of types of items

    int numFainted = 0;                                   // number of fainted Pokémon

    std::vector<std::unique_ptr<Pokemon>> party;
    std::array<std::vector<std::unique_ptr<Item>>, Trainer::NUM_ITEM_TYPES> items;

    static std::size_t getItemTypeId() {
        static std::size_t lastId = 0ULL;
        return lastId++;
    }

    template<typename I>
    static std::size_t getItemTypeId() {
        const static std::size_t type_id = Trainer::getItemTypeId();
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

    template<typename P, typename ...Args>
    void addPokemon(Args ...params) {
        if (this->party.size() == Trainer::MAX_POKEMON) {
            return;
        }

        this->party.push_back(std::make_unique<P>(params...));
    }

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
        return *static_cast<I *>(ptr);
    }

    template<typename I>
    const I &getItem(int index) const {
        Item *ptr = this->items.at(Trainer::getItemTypeId<I>())[index].get();
        return *static_cast<I *>(ptr);
    }

    void addItem(std::unique_ptr<Item> toAdd);

    template<typename I>
    void addItem(const I &item) {
        try {
            if (this->items.at(static_cast<std::size_t>(item.getClass())).size() == Trainer::MAX_ITEMS) {
                return;
            }

            for (const auto &i : this->items.at(static_cast<std::size_t>(item.getClass()))) {
                // if item already exists within our inventory
                if (i->getId() == item.getId()) {
                    i->add(item.getQuantity());
                    return;
                }
            }

            std::unique_ptr<Item> i = std::make_unique<I>(item.getQuantity());
            this->items.at(static_cast<std::size_t>(item.getClass())).push_back(std::move(i));
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Error adding item: ") + e.what() + '\n');
        }
    }

    template<typename I, typename ...Args>
    void addItem(Args ...params) {
        try {
            std::unique_ptr<I> item = std::make_unique<I>(params...);

            if (this->items.at(static_cast<std::size_t>(item->getClass())).size() == Trainer::MAX_ITEMS) {
                return;
            }

            for (const auto &i : this->items.at(static_cast<std::size_t>(item->getClass()))) {
                // if item already exists within our inventory
                if (i->getId() == item->getId()) {
                    i->add(item->getQuantity());
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

    explicit operator bool() const override;

    [[nodiscard]] virtual bool canFight() const;
};
