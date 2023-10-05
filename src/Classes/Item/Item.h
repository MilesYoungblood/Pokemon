//
// Created by miles on 5/25/2022.
//

#pragma once

#include <iostream>

#include "../../Classes/Pokemon/Pokemon.h"

enum class RestoreType { NONE, HP, PP };
enum class Stat { NONE, ATTACK, SP_ATTACK, DEFENSE, SP_DEFENSE, SPEED, ACCURACY };

class Item {
protected:
    const char *name;
    int quantity;

public:
    Item();
    Item(const char *name, int n);
    virtual ~Item() = default;

    __attribute__((unused)) void setQuantity(int newQuantity);
    int getQuantity() const;

    void use();
    virtual void useMessage();

    virtual int getAmount() const;
    virtual RestoreType getRestoreType() const;
    virtual Status getStatus() const;
    virtual Stat getStat() const;

    virtual void restore(Pokemon &pokemon) = 0;
    virtual void restore(Move &move) = 0;
    virtual void restoreMessage(Pokemon &pokemon) = 0;
    virtual void restoreMessage(Move &move) = 0;

    std::string getName() const;

    explicit operator bool() const;

    friend std::ostream& operator<<(std::ostream &out, const Item &rhs);
};