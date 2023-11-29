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
public:
    enum class Id {
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

    struct Data {
        std::string_view name;
        std::string_view description;
        int power;
        int accuracy;
        Type type;
        Move::Category category;
        bool priority;
        bool sureHit;
    };

    explicit Move(Move::Id id);

    Move(Move::Id id, int pp, int maxPp);

    Move(const Move &) = delete;

    Move(Move &&) noexcept;

    Move &operator=(const Move &) = delete;

    Move &operator=(Move &&rhs) noexcept;

    virtual ~Move() = default;

    static void initData(Move::Data (*instructions)(Move::Id));

    void restore(int amount);

    void use();

    [[nodiscard]] int getPp() const;

    [[nodiscard]] int getMaxPp() const;

    void fillToMax();

    [[nodiscard]] virtual int getDamage() const;

    virtual void action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool &skip);

    virtual void actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, int damage, bool skipTurn, bool criticalHit, double typeEff);

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] const char *getDescription() const;

    [[nodiscard]] int getPower() const;

    [[nodiscard]] int getAccuracy() const;

    [[nodiscard]] Type getType() const;

    [[nodiscard]] Move::Category getCategory() const;

    [[nodiscard]] Move::Id getId() const;

    [[nodiscard]] bool isPriority() const;

    explicit operator bool() const;

private:
    Move::Id id;
    int pp;
    int maxPp;

    inline static Move::Data (*dataFunction)(Move::Id){ nullptr };
};
