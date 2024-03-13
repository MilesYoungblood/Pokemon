//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include "../../../Item/DerivedClasses/Items.h"

class Trainer : public Character {
private:
    enum : Uint8 {
        MAX_POKEMON = 6,
        MAX_ITEMS = 50
    };

    bool keepLooping{ true };

    std::vector<std::unique_ptr<Pokemon>> party;
    std::unordered_map<std::size_t, std::unordered_map<std::string, std::unique_ptr<Item>>> items;

    void init();

protected:
    Trainer(const char *id, int x, int y, Direction direction);

    [[nodiscard]] std::size_t partySize() const;

public:
    Trainer(const char *id, const char *name, int x, int y, Direction direction, int vision);

    Trainer(const Trainer &) = delete;

    Trainer(Trainer &&toMove) noexcept = default;

    Trainer &operator=(const Trainer &) = delete;

    Trainer &operator=(Trainer &&) noexcept = delete;

    ~Trainer() override = default;

    void addPokemon(const char *id);

    void addPokemon(std::unique_ptr<Pokemon> toAdd);

    void removePokemon(long long int index);

    void swapPokemon(std::size_t a, std::size_t b);

    void clearParty();

    template<typename I>
    [[nodiscard]] std::size_t getNumItems() const {
        try {
            return this->items.at(typeid(I).hash_code()).size();
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Unable to retrieve item count: ") + e.what() + '\n');
        }
    }

    template<typename I>
    I &getItem(const std::string &id) {
        try {
            return *dynamic_cast<I *>(this->items.at(typeid(I).hash_code()).at(id).get());
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Unable to retrieve item: ") + e.what() + '\n');
        }
    }

    void addItem(const std::string &id, int n);

    void addItem(std::unique_ptr<Item> item);

    template<typename I>
    void removeItem(const std::string &id) {
        try {
            this->items.at(typeid(I).hash_code()).erase(id);
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Error removing item: ") + e.what() + '\n');
        }
    }

    Pokemon &operator[](std::size_t index);

    std::vector<std::unique_ptr<Pokemon>>::iterator begin();

    std::vector<std::unique_ptr<Pokemon>>::const_iterator begin() const;

    std::vector<std::unique_ptr<Pokemon>>::iterator end();

    std::vector<std::unique_ptr<Pokemon>>::const_iterator end() const;

    virtual void handleFaint();

    void idle() override;

    [[nodiscard]] virtual std::vector<std::string> winMessage() const;

    [[nodiscard]] bool canFight() const override;

    [[nodiscard]] bool isTrainer() const override;

    void interact() override;
};
