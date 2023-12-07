//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../AutoThread/AutoThread.h"
#include "../../Functions/GeneralFunctions.h"

enum class Type {
    NONE, NORMAL, FIRE, WATER, ELECTRIC, GRASS,
    ICE, FIGHTING, POISON, GROUND, FLYING,
    PSYCHIC, BUG, ROCK, GHOST, DRAGON,
    DARK, STEEL
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
        VOLT_TACKLE
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

    explicit Move(int pp);

    Move(int pp, int maxPp);

    Move(const Move &) = delete;

    Move(Move &&) noexcept = delete;

    Move &operator=(const Move &) = delete;

    Move &operator=(Move &&rhs) noexcept = delete;

    virtual ~Move() = default;

    void setPp(int amount);

    void setMaxPp(int amount);

    void restore(int amount);

    void use();

    [[nodiscard]] int getPp() const;

    [[nodiscard]] int getMaxPp() const;

    void fillToMax();

    [[nodiscard]] virtual int getDamage() const;

    virtual void action(Pokemon &attacker, Pokemon &defender, bool &skip);

    [[nodiscard]] virtual std::queue<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender, bool skip) const;

    [[nodiscard]] virtual std::string getName() const = 0;

    [[nodiscard]] virtual const char *getDescription() const = 0;

    [[nodiscard]] virtual int getPower() const = 0;

    [[nodiscard]] virtual int getAccuracy() const;

    [[nodiscard]] virtual double getCritRatio() const;

    [[nodiscard]] virtual Type getType() const = 0;

    [[nodiscard]] virtual Move::Category getCategory() const = 0;

    [[nodiscard]] virtual Move::Id getId() const = 0;

    [[nodiscard]] virtual bool isPriority() const;

    explicit operator bool() const;

protected:
    void resetFlags();

    void setDamageFlag(int amount);

    [[nodiscard]] int getDamageFlag() const;

    void setEffFlag(double amount);

    [[nodiscard]] double getEffFlag() const;

    void setCritFlag(double amount);

    [[nodiscard]] double getCritFlag() const;

    void calculateDamage(const Pokemon &attacker, const Pokemon &defender);

private:
    [[nodiscard]] double checkType(const Pokemon &pokemon) const;

    int pp;
    int maxPp;

    int damageFlag{ 0 };
    double effFlag{ 0.0 };
    double critFlag{ 0.0 };
};

inline std::mutex moveMutex;
inline std::unordered_map<Move::Id, std::unique_ptr<Move>(*)()> moveMap;
