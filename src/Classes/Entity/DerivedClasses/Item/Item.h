//
// Created by miles on 5/25/2022.
//

#pragma once

#include "../Character/DerivedClasses/Pokemon/Pokemon.h"

class Item : public Entity {
private:
    int quantity;

public:
    explicit Item(int n);

    Item(int n, int x, int y);

    Item(const Item &toCopy) = delete;

    Item(Item &&) noexcept = delete;

    Item &operator=(const Item &) = delete;

    Item &operator=(Item &&) noexcept = delete;

    ~Item() override = default;

    [[nodiscard]] int getQuantity() const;

    void add(int n);

    void use();

    [[nodiscard]] virtual std::string useMessage() const;

    [[nodiscard]] std::string noEffectMessage(const Pokemon &pokemon) const;

    [[nodiscard]] virtual std::string getName() const = 0;

    [[nodiscard]] virtual std::string getEffect() const = 0;

    [[nodiscard]] virtual std::size_t getClass() const = 0;

    void interact() override;

    void update() override;

    void render() const override;

    [[nodiscard]] bool canUse() const;
};

inline std::mutex itemMutex;
inline std::unordered_map<std::string, std::unique_ptr<Item> (*)(int)> itemMap;
