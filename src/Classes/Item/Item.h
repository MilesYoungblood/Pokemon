//
// Created by miles on 5/25/2022.
//

#pragma once

#include <iostream>

#include "../../Classes/Pokemon/Pokemon.h"

enum ItemID {
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

    X_ATTACK,
    X_DEFENSE,
    X_SP_ATTACK,
    X_SP_DEFENSE,
    X_SPEED,
    X_ACCURACY
};

enum class RestoreType { NONE, HP, PP };
enum class Stat { NONE, ATTACK, DEFENSE, SP_ATTACK, SP_DEFENSE, SPEED, ACCURACY };

class Item {
protected:
    const char *name;
    int quantity;

public:
    Item();
    Item(const char *name, int n);
    virtual ~Item() = default;

    void setQuantity(int newQuantity);
    [[nodiscard]] int getQuantity() const;

    void use();
    virtual void useMessage();

    [[nodiscard]] virtual int getAmount() const;
    [[nodiscard]] virtual RestoreType getRestoreType() const;
    [[nodiscard]] virtual Status getStatus() const;
    [[nodiscard]] virtual Stat getStat() const;

    virtual void restore(Pokemon &pokemon) = 0;
    virtual void restore(Move &move) = 0;
    virtual void restoreMessage(const Pokemon &pokemon) = 0;
    virtual void restoreMessage(const Move &move) = 0;
    virtual bool catchPokemon(const Pokemon &pokemon, bool attempts[]) = 0;

    [[nodiscard]] std::string getName() const;

    explicit operator bool() const;

    friend std::ostream& operator<<(std::ostream &out, const Item &rhs);
};
