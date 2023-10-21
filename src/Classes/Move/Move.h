//
// Created by miles on 5/5/2022.
//

#pragma once

#include <iostream>
#include <random>
#include <thread>

#include "../../Functions/GeneralFunctions.h"

enum class Category { PHYSICAL, SPECIAL, STATUS };

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
    const char *name;

    int pp;
    int maxPp;
    int power;
    int accuracy;

    Type type;
    Category category;

public:
    Move(const char *name, int pp, int power, int accuracy, Type type, Category category);
    Move(const Move &) = delete;
    auto operator=(const Move &) -> Move& = delete;
    Move(const Move &&) = delete;
    auto operator=(const Move &&) -> Move& = delete;
    virtual ~Move() = default;

    virtual auto getID() -> MoveID = 0;

    [[nodiscard]] virtual auto getDamage() const -> int;

    virtual void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool &skip);
    virtual void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, int damage, bool skipTurn, bool criticalHit, double typeEff);

    void use();
    void setPP(int newPP);
    [[nodiscard]] auto getPP() const -> int;

    [[nodiscard]] auto getMaxPP() const -> int;

    [[nodiscard]] auto getPower() const -> int;

    [[nodiscard]] auto getAccuracy() const -> int;

    [[nodiscard]] auto getType() const -> Type;
    [[nodiscard]] auto getTypeAsString() const -> const char *;

    [[nodiscard]] auto getCategory() const -> Category;
    [[nodiscard]] auto getCategoryAsString() const -> const char *;

    [[nodiscard]] auto getName() const -> std::string;

    explicit operator bool() const;

    friend auto operator<<(std::ostream &out, const Move &rhs) -> std::ostream&;
};
