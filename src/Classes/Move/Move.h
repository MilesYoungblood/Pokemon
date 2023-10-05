//
// Created by miles on 5/5/2022.
//

#pragma once

#include <iostream>
#include <random>
#include <thread>

#include "../../main.h"

enum class Category { PHYSICAL, SPECIAL, STATUS };

enum class Type {
    NONE, NORMAL, FIRE, WATER, ELECTRIC, GRASS,
    ICE, FIGHTING, POISON, GROUND, FLYING,
    PSYCHIC, BUG, ROCK, GHOST, DRAGON,
    DARK, STEEL, FAIRY
};

class Pokemon;

class Move {
protected:
    const char *name;

    int pp;
    int maxPp;
    int power;
    int accuracy;

    Type type;
    Category category;

public:
    Move(const char *name, int pp, int power, int accuracy, Type type, Category category);
    Move(const Move &moveToCopy) = delete;
    Move& operator=(const Move &rhs) = delete;

    virtual int getDamage();

    virtual void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage);
    virtual void actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, double typeEff);

    void setPP(int newPP);
    int getPP() const;

    int getMaxPP() const;

    int getPower() const;

    int getAccuracy() const;

    Type getType() const;

    Category getCategory() const;

    std::string getName() const;

    explicit operator bool() const;

    friend std::ostream& operator<<(std::ostream &out, const Move &rhs);
};