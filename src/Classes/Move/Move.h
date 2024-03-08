//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../../Enums/Type/Type.h"
#include "../../Functions/GeneralFunctions.h"

class Pokemon;

enum Effect : Uint8 {
    BINDING,
    CONSECUTIVE,
    HP_DRAINING,
    RAISE_STAT,
    LOWER_STAT,
    CAN_FLINCH,
    CAN_CONFUSE,
    CAN_BURN,
    CAN_FREEZE,
    CAN_PARALYZE,
    CAN_POISON,
    CAN_SLEEP,
    CANNOT_MISS,
    CAUSE_FAINT,
    CHANGE_TYPE,
    COST_HP,
    HAVE_RECOIL,
    REQUIRE_RECHARGE,
    RESTORE_HP,
    SWITCH_OUT_USER,
    SWITCH_OUT_TARGET,
    THAW_OUT_USER,
    CHARGING_TURN,
    SEMI_INVULNERABLE,
    MULTI_STRIKE,
    PROTECTION
};

class Move {
public:
    enum class Id : Uint8 {
        AIR_SLASH,
        AURA_SPHERE,
        DARK_PULSE,
        DRAGON_PULSE,
        EXTRASENSORY,
        FLAMETHROWER,
        FLASH_CANNON,
        FOCUS_BLAST,
        HEAD_SMASH,
        HEAT_CRASH,
        ICE_BEAM,
        IRON_TAIL,
        QUICK_ATTACK,
        SOLAR_BEAM,
        THUNDER,
        VOLT_TACKLE
    };

    enum class Category : Uint8 {
        PHYSICAL, SPECIAL, STATUS
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

    virtual void action(Pokemon &attacker, Pokemon &defender, bool &skip);

    [[nodiscard]] virtual std::vector<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender, bool skip) const;

    [[nodiscard]] virtual std::string getName() const = 0;

    [[nodiscard]] virtual std::string getDescription() const = 0;

    [[nodiscard]] virtual int getPower(const Pokemon &attacker, const Pokemon &defender) const = 0;

    [[nodiscard]] virtual int getAccuracy() const;

    [[nodiscard]] virtual double getCritRatio() const;

    [[nodiscard]] virtual Type getType() const = 0;

    [[nodiscard]] virtual Move::Category getCategory() const = 0;

    [[nodiscard]] virtual Move::Id getId() const = 0;

    [[nodiscard]] virtual bool isPriority() const;

    explicit operator bool() const;

protected:
    void resetFlags();

    [[nodiscard]] int getDamageFlag() const;

    [[nodiscard]] double getEffFlag() const;

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
