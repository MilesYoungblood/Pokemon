//
// Created by miles on 5/25/2022.
//

#pragma once

#include "../Entity/DerivedClasses/Pokemon/Pokemon.h"

enum Time {
    MORNING, DAY, NIGHT
};

class Item {
private:
    int quantity;

public:
    enum class Class {
        RESTORE,
        STATUS,
        POKE_BALL,
        BATTLE
    };

    explicit Item(int n);

    Item(const Item &toCopy);

    Item(Item &&) noexcept = delete;

    Item &operator=(const Item &) = delete;

    Item &operator=(Item &&) noexcept = delete;

    virtual ~Item() = default;

    [[nodiscard]] virtual std::string getName() const = 0;

    [[nodiscard]] int getQuantity() const;

    void add(int n = 1);

    void use();

    virtual void useMessage();

    [[nodiscard]] virtual Item::Class getClass() const = 0;

    explicit operator bool() const;
};
