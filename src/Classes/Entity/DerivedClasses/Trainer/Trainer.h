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

    int numFainted = 0;                                   // number of fainted Pokémon

    std::vector<std::unique_ptr<Pokemon>> party;
    std::unordered_map<std::size_t, std::vector<std::unique_ptr<Item>>> items;

public:
    Trainer();

    Trainer(const char *name, int x, int y);

    Trainer(const char *name, int x, int y, Direction direction);

    Trainer(const char *name, int x, int y, Direction direction, int vision);

    Trainer(const Trainer &) = delete;

    Trainer(Trainer &&) noexcept = delete;

    Trainer &operator=(const Trainer &) = delete;

    Trainer &operator=(Trainer &&) noexcept = delete;

    ~Trainer() override = default;

    [[nodiscard]] std::size_t partySize() const;

    void addPokemon(std::unique_ptr<Pokemon> toAdd);

    void removePokemon(long long int index);

    void swapPokemon(std::size_t a, std::size_t b);

    void clearParty();

    template<typename I>
    [[nodiscard]] std::size_t getNumItems() const {
        try {
            return this->items.at(typeid(I).hash_code()).size();
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Unable to retrieve item count: ") + e.what() + '\n');
        }
    }

    template<typename I>
    I &getItem(std::size_t index) {
        Item *ptr = this->items.at(typeid(I).hash_code())[index].get();
        return *dynamic_cast<I *>(ptr);
    }

    template<typename C, typename I>
    void addItem(std::unique_ptr<I> item) {
        try {
            if (this->items.at(typeid(C).hash_code()).size() == Trainer::MAX_ITEMS) {
                return;
            }

            for (std::size_t i = 0; i < this->items.at(typeid(C).hash_code()).size(); ++i) {
                // if item already exists within our inventory
                Item *ptr = this->items.at(typeid(C).hash_code()).at(i).get();
                const C *itm = dynamic_cast<C *>(ptr);

                if (item->getId() == itm->getId()) {
                    this->items.at(typeid(C).hash_code())[i]->add(item->getQuantity());
                    return;
                }
            }

            this->items.at(typeid(C).hash_code()).push_back(std::move(item));
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Error adding item: ") + e.what() + '\n');
        }
    }

    template<typename I>
    void removeItem(long long int index) {
        try {
            const std::size_t i = typeid(I).hash_code();
            this->items.at(i).erase(this->items.at(i).begin() + index);
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Error removing item: ") + e.what() + '\n');
        }
    }

    void incFaintCount();

    void decFaintCount();

    [[nodiscard]] int getFaintCount() const;

    Pokemon &operator[](std::size_t index);

    const Pokemon &operator[](std::size_t index) const;

    std::vector<std::unique_ptr<Pokemon>>::iterator begin();

    std::vector<std::unique_ptr<Pokemon>>::iterator end();

    [[nodiscard]] bool canFight() const override;
};
