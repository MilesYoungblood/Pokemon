//
// Created by miles on 5/5/2022.
//

#pragma once

#include <string>
#include <random>
#include <thread>

#include "../../Functions/GeneralFunctions.h"

enum class Category {
    PHYSICAL, SPECIAL, STATUS
};

enum MoveID {
    AIR_SLASH,
    AURA_SPHERE,
    DARK_PULSE,
    DRAGON_PULSE,
    EXTRASENSORY,
    FLAMETHROWER,
    FLASH_CANNON,
    FOCUS_BLAST,
    ICE_BEAM,
    IRON_TAIL,
    QUICK_ATTACK,
    SOLAR_BEAM,
    THUNDER,
    VOLT_TACKLE,
    WATER_SHURIKEN
};

enum class Type {
    NONE, NORMAL, FIRE, WATER, ELECTRIC, GRASS,
    ICE, FIGHTING, POISON, GROUND, FLYING,
    PSYCHIC, BUG, ROCK, GHOST, DRAGON,
    DARK, STEEL, FAIRY
};

class Pokemon;

class Move {
private:
    int pp;
    int maxPp;

public:
    explicit Move(int pp);

    Move(const Move &) = delete;

    Move(const Move &&) = delete;

    Move &operator=(const Move &) = delete;

    Move &operator=(const Move &&) = delete;

    virtual ~Move() = default;

    [[nodiscard]] virtual int getDamage() const;

    virtual void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool &skip);

    virtual void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, int damage, bool skipTurn, bool criticalHit, double typeEff);

    void use();

    void setPP(int newPP);

    void fillToMax();

    [[nodiscard]] int getPP() const;

    [[nodiscard]] int getMaxPP() const;

    [[nodiscard]] virtual int getPower() const = 0;

    [[nodiscard]] virtual int getAccuracy() const;

    [[nodiscard]] virtual Type getType() const = 0;

    [[nodiscard]] virtual Category getCategory() const = 0;

    [[nodiscard]] virtual MoveID getID() const = 0;

    [[nodiscard]] virtual std::string getName() const = 0;

    [[nodiscard]] virtual const char *getDescription() const = 0;

    [[nodiscard]] virtual bool isPriority() const;

    explicit operator bool() const;
};
