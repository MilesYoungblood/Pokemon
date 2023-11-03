//
// Created by miles on 5/25/2022.
//

#pragma once

#include <iostream>

#include "../Entity/DerivedClasses/Pokemon/Pokemon.h"

enum Time {
    MORNING, DAY, NIGHT
};

enum class ItemType {
    RESTORE,
    STATUS,
    POKE_BALL,
    BATTLE
};

enum class ItemID {
    POTION,
    SUPER_POTION,
    HYPER_POTION,
    ETHER,

    ANTIDOTE,
    AWAKENING,
    BURN_HEAL,
    ICE_HEAL,
    PARALYZE_HEAL,

    POKE_BALL,
    GREAT_BALL,
    ULTRA_BALL,
    MASTER_BALL,
    NET_BALL,
    NEST_BALL,
    TIMER_BALL,
    PREMIER_BALL,
    DUSK_BALL,
    HEAL_BALL,
    QUICK_BALL,

    X_ATTACK,
    X_DEFENSE,
    X_SP_ATTACK,
    X_SP_DEFENSE,
    X_SPEED,
    X_ACCURACY
};

enum class Stat {
    NONE, ATTACK, DEFENSE, SP_ATTACK, SP_DEFENSE, SPEED, ACCURACY
};

class Item {
private:
    int quantity{ 0 };

public:
    Item() = default;

    explicit Item(int n);

    Item(const Item &) = delete;

    Item(const Item &&) = delete;

    Item &operator=(const Item &) = delete;

    Item &operator=(const Item &&) = delete;

    virtual ~Item() = default;

    [[nodiscard]] int getQuantity() const;

    void use();

    virtual void useMessage();

    void add();

    [[nodiscard]] virtual std::string getName() const = 0;

    [[nodiscard]] virtual ItemID getID() const = 0;

    [[nodiscard]] virtual ItemType getType() const = 0;

    explicit operator bool() const;
};
