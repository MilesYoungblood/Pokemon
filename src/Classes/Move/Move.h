//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../../Functions/GeneralFunctions.h"

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
    enum Id {
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

    enum class Category {
        PHYSICAL, SPECIAL, STATUS
    };

    explicit Move(int pp);

    Move(int pp, int maxPp);

    Move(const Move &) = delete;

    Move(Move &&) noexcept = delete;

    Move &operator=(const Move &) = delete;

    Move &operator=(Move &&) noexcept = delete;

    virtual ~Move() = default;

    void use();

    void setPp(int newPp);

    [[nodiscard]] int getPp() const;

    [[nodiscard]] int getMaxPp() const;

    [[nodiscard]] virtual int getDamage() const;

    virtual void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool &skip);

    virtual void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, int damage, bool skipTurn, bool criticalHit, double typeEff);

    [[nodiscard]] virtual int getPower() const = 0;

    [[nodiscard]] virtual int getAccuracy() const;

    [[nodiscard]] virtual Type getType() const = 0;

    [[nodiscard]] virtual Move::Category getCategory() const = 0;

    [[nodiscard]] virtual Move::Id getId() const = 0;

    [[nodiscard]] virtual std::string getName() const = 0;

    [[nodiscard]] virtual const char *getDescription() const = 0;

    [[nodiscard]] virtual bool isPriority() const;

    explicit operator bool() const;
};
